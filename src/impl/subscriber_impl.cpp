#include "subscriber_impl.h"

#include "ezcom/exception.h"
#include "proto/gen/ezcom.pb.h"
#include "zmq.h"

namespace ezcom {
namespace impl {

SubscriberImpl::SubscriberImpl(void* context,
                               const TransportType& transport_type) {
  node_type_ = NodeType::kSubscriber;
  comm_mode_ = CommMode::kPubSub;
  transport_type_ = transport_type;
  // Create zmq socket
  if (context == nullptr) {
    throw InvalidParamException("Zmq context is nullptr");
  }
  context_ = context;
  socket_ = zmq_socket(context_, ZMQ_SUB);
}

SubscriberImpl::SubscriberImpl(const TransportType& transport_type)
    : SubscriberImpl(zmq_ctx_new(), transport_type) {}

SubscriberImpl::~SubscriberImpl() {
  recv_running_ = false;
  if (recv_thread_->joinable()) {
    recv_thread_->join();
  }

  // destory zmq resources
  zmq_close(socket_);
  if (transport_type_ != TransportType::kZmqInproc) {
    zmq_ctx_term(context_);
  }
}

void SubscriberImpl::Subscribe(const std::string& addr,
                               const MsgCallback& msg_cb,
                               const std::string& topic) {
  static std::atomic_bool connect{false};
  if (connect) {
    throw AlreadyDoneException("Subscriber has already been connected");
  }
  if (addr.empty()) {
    throw InvalidParamException("Invalid addr");
  }
  if (msg_cb == nullptr) {
    throw InvalidParamException("Invalid msg callback function");
  }
  topic_ = topic;

  // set socketopt
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

  setopt_rc += zmq_setsockopt(socket_, ZMQ_RCVTIMEO, &kZmqRcvTimeout,
                      sizeof(kZmqRcvTimeout));
  setopt_rc += zmq_setsockopt(socket_, ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
  if (setopt_rc != 0) {
    throw ResourceException("Zmq setsockopt failed");
  }

  // connect socket
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
  connect = true;
  recv_running_ = true;
  recv_thread_ = std::make_shared<std::thread>(
      std::bind(&SubscriberImpl::RecvThread, this, msg_cb));
}

void SubscriberImpl::RecvThread(const MsgCallback& msg_cb) {
  while (recv_running_) {
    zmq_msg_t z_msg;
    zmq_msg_init(&z_msg);
    int rc = zmq_msg_recv(&z_msg, socket_, 0);
    if (rc == -1) {
      zmq_msg_close(&z_msg);
      if (zmq_errno() == EAGAIN) {
        continue;
      }
      throw ResourceException("Zmq recv failed");
    }
    auto message = std::make_shared<Message>();
    message->GetProtobufMessage()->ParseFromArray(
        (char*)zmq_msg_data(&z_msg) + topic_.size(), zmq_msg_size(&z_msg));
    zmq_msg_close(&z_msg);
    // call callback
    msg_cb(message);
  }
}

}  // namespace impl
}  // namespace ezcom
