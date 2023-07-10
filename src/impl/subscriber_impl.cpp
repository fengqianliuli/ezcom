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
  if (addr.empty()) {
    throw InvalidParamException("Invalid addr");
  }
  topic_ = topic;
  int rc = -1;
  // set socketopt
  rc = zmq_setsockopt(socket_, ZMQ_RCVTIMEO, &kZmqRcvTimeout,
                      sizeof(kZmqRcvTimeout));
  rc = zmq_setsockopt(socket_, ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
  if (rc != 0) {
    throw ResourceException("Zmq setsockopt failed");
  }

  // connect socket
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
