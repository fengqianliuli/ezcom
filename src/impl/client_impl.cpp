#include "client_impl.h"

#include "ezcom/exception.h"
#include "proto/gen/ezcom.pb.h"
#include "utils/timer_scheduler.h"
#include "utils/zmq_utils.h"
#include "zmq.h"

namespace ezcom {
namespace impl {

ClientImpl::ClientImpl(const TransportType& transport_type)
    : ClientImpl(zmq_ctx_new(), transport_type) {}

ClientImpl::ClientImpl(void* context, const TransportType& transport_type) {
  node_type_ = NodeType::kClient;
  comm_mode_ = CommMode::kReqRep;
  transport_type_ = transport_type;
  // Create zmq socket
  if (context == nullptr) {
    throw InvalidParamException("Zmq context is nullptr");
  }
  context_ = context;
  socket_ = zmq_socket(context_, ZMQ_REQ);
  // Create zmq monitor
  monitor_socket_ = utils::ZmqUtils::CreateMonitorSockets(context_, socket_,
                                                          "req-rep-client");
  msg_queue_ = std::make_shared<utils::ThreadSafeQueue<impl::MsgPack>>();
  msg_id_set_ = std::make_shared<std::set<uint64_t>>();
  promise_map_ = std::make_shared<PromiseMap>();
  msg_send_thread_ =
      std::make_shared<std::thread>(std::bind(&ClientImpl::MsgSendLoop, this));
  utils::TimerScheduler::run();
}

ClientImpl::~ClientImpl() {
  utils::TimerScheduler::reset();
  promise_map_->clear();
  msg_queue_->BreakAllWait();
  if (msg_send_thread_->joinable()) {
    msg_send_thread_->join();
  }

  monitor_running_ = false;
  monitor_future_.get();

  // destory zmq resources
  zmq_close(socket_);
  zmq_close(monitor_socket_);
  if (transport_type_ != TransportType::kZmqInproc) {
    zmq_ctx_term(context_);
  }
}

void ClientImpl::MsgSendLoop() {
  MsgPack msg_pack;
  while (msg_queue_->WaitDequeue(&msg_pack)) {
    auto& req_msg = msg_pack.req_message;
    auto& cb = msg_pack.return_msg_cb;
    // ZMQ send
    zmq_msg_t z_msg;
    zmq_msg_init_size(&z_msg, req_msg->GetProtobufMessage()->ByteSizeLong());
    req_msg->GetProtobufMessage()->SerializeToArray(
        zmq_msg_data(&z_msg), req_msg->GetProtobufMessage()->ByteSizeLong());
    int rc = zmq_msg_send(&z_msg, socket_, 0);
    zmq_msg_close(&z_msg);
    if (rc == -1) {
      throw ResourceException("Zmq send failed");
    }

    // ZMQ recv
    zmq_msg_t z_reply;
    zmq_msg_init(&z_reply);
    rc = zmq_msg_recv(&z_reply, socket_, 0);
    if (rc == -1) {
      throw ResourceException("Zmq recv failed");
    }
    req_msg->GetProtobufMessage()->ParseFromArray(zmq_msg_data(&z_reply),
                                                  zmq_msg_size(&z_reply));
    zmq_msg_close(&z_reply);
    if (cb != nullptr) {
      cb(req_msg);
    }
  }
}

void ClientImpl::Connect(const std::string& addr,
                         const ConnectionCallback& conn_cb) {
  if (connected_) {
    throw AlreadyDoneException("Client has already been connected");
  }
  if (addr.empty()) {
    throw InvalidParamException("Invalid addr");
  }

  // set keep alive trun on
  int tcp_keep_alive = 1;
  // set keep alive idle, unit: s
  int tcp_keep_alive_idle = 120;
  // set keep alive count, unit: times
  int tcp_keep_alive_count = 3;
  // set keep alive interval, unit: s
  int tcp_keep_alive_interval = 5;
  int setopt_rc = 0;
  setopt_rc += zmq_setsockopt(socket_, ZMQ_TCP_KEEPALIVE, &tcp_keep_alive,
                       sizeof(tcp_keep_alive));
  setopt_rc += zmq_setsockopt(socket_, ZMQ_TCP_KEEPALIVE_IDLE, &tcp_keep_alive_idle,
                       sizeof(tcp_keep_alive_idle));
  setopt_rc += zmq_setsockopt(socket_, ZMQ_TCP_KEEPALIVE_CNT, &tcp_keep_alive_count,
                       sizeof(tcp_keep_alive_count));
  setopt_rc +=
      zmq_setsockopt(socket_, ZMQ_TCP_KEEPALIVE_INTVL, &tcp_keep_alive_interval,
                     sizeof(tcp_keep_alive_interval));
  if (setopt_rc != 0) {
    throw ResourceException("Zmq setsockopt failed");
  }

  int rc = -1;
  switch (transport_type_) {
    case TransportType::kZmqInproc: {
      rc = zmq_connect(socket_, ("inproc://" + addr).c_str());
    } break;
    case TransportType::kZmqIpc: {
      rc = zmq_connect(socket_, ("ipc:///tmp/" + addr).c_str());
    } break;
    case TransportType::kZmqTcp: {
      // 判断addr是否是ip地址
      if (addr.find(':') == std::string::npos) {
        throw InvalidParamException("Invalid ip address: " + addr);
      }
      rc = zmq_connect(socket_, ("tcp://" + addr).c_str());
    } break;
    default:
      throw InvalidParamException("Unknown transport type");
  }
  if (rc != 0) {
    throw ResourceException("Zmq connect failed");
  }
  connected_ = true;
  if (conn_cb) {
    monitor_running_ = true;
    monitor_future_ = std::async(std::launch::async, [this, conn_cb]() {
      while (monitor_running_) {
        int event = utils::ZmqUtils::GetMonitorEvent(monitor_socket_);
        if (event == -1) continue;
        if (event == ZMQ_EVENT_CONNECTED) {
          conn_cb(ConnectionEvent::kConnected);
        } else if (event == ZMQ_EVENT_DISCONNECTED) {
          conn_cb(ConnectionEvent::kDisconnected);
        }
      }
    });
  }
}

Result ClientImpl::SyncRequest(const std::shared_ptr<Message>& req_message,
                               int timeout_ms) {
  if (!connected_) {
    return {ResultType::kConditionCheckError, nullptr};
  }
  if (req_message == nullptr) {
    return {ResultType::kInvaildParam, nullptr};
  }
  // generate msg id
  uint64_t msg_id = msg_id_.fetch_add(1);
  msg_id_set_->insert(msg_id);
  req_message->SetMsgId(msg_id);
  // create promise and future
  std::promise<const std::shared_ptr<Message>&> promise;
  auto future = promise.get_future();
  // when client timeout and return, but server msg reply call the function.
  // promise_map will be erase promise by msg id.
  // future could not be destroyed when client timeout and return,
  // promise and future must be destroyed together when server reply msg back.
  promise_map_->emplace(msg_id,
                        std::make_pair(std::move(promise), std::move(future)));
  msg_queue_->Enqueue(
      {req_message, [this](const std::shared_ptr<Message>& rep_message) {
         if (promise_map_ != nullptr &&
             promise_map_->find(rep_message->GetMsgId()) !=
                 promise_map_->end()) {
           promise_map_->at(rep_message->GetMsgId())
               .first.set_value(rep_message);
           msg_id_set_->erase(rep_message->GetMsgId());
         }
       }});
  // wait callback in timeout
  if (timeout_ms <= 0) {
    auto& tmp_msg = promise_map_->at(msg_id).second.get();
    promise_map_->erase(msg_id);
    return {ResultType::kSuccess, tmp_msg};
  } else {
    auto status = promise_map_->at(msg_id).second.wait_for(
        std::chrono::milliseconds(timeout_ms));
    switch (status) {
      case std::future_status::ready: {
        auto& tmp_msg = promise_map_->at(msg_id).second.get();
        promise_map_->erase(msg_id);
        return {ResultType::kSuccess, tmp_msg};
      } break;
      case std::future_status::timeout: {
        return {ResultType::kTimeout, nullptr};
      } break;
      case std::future_status::deferred: {
        return {ResultType::kTimeout, nullptr};
      } break;
    }
  }
  return {ResultType::kUnknownError, nullptr};
}

void ClientImpl::AsyncRequest(const std::shared_ptr<Message>& req_message,
                              const ResultCallback& result_cb, int timeout_ms) {
  if (!connected_) {
    result_cb({ResultType::kConditionCheckError, nullptr});
    return;
  }
  if (req_message == nullptr) {
    result_cb({ResultType::kInvaildParam, nullptr});
    return;
  }
  // generate msg id
  uint64_t msg_id = msg_id_.fetch_add(1);
  msg_id_set_->insert(msg_id);
  req_message->SetMsgId(msg_id);
  // timing, if request timeout, timer will call function and return timeout
  utils::TimerScheduler::TimerHandle time_handle{-1};
  if (timeout_ms > 0) {
    time_handle = utils::TimerScheduler::addTimer(
        std::chrono::milliseconds(timeout_ms),
        [this, &result_cb, msg_id](utils::TimerScheduler::TimerHandle handle) {
          utils::TimerScheduler::removeTimer(handle);
          msg_id_set_->erase(msg_id);
          result_cb({ResultType::kTimeout, nullptr});
        });
  }

  // when client timeout and return, but server msg reply call the function.
  // so, need to check msg id has been erase.
  msg_queue_->Enqueue(
      {req_message, [this, &result_cb, time_handle,
                     timeout_ms](const std::shared_ptr<Message>& rep_message) {
         if (msg_id_set_->find(rep_message->GetMsgId()) == msg_id_set_->end()) {
           return;
         }
         if (timeout_ms > 0) {
           utils::TimerScheduler::removeTimer(time_handle);
         }
         msg_id_set_->erase(rep_message->GetMsgId());
         result_cb({ResultType::kSuccess, rep_message});
       }});
}

}  // namespace impl
}  // namespace ezcom
