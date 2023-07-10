#include "publisher_impl.h"

#include "ezcom/exception.h"
#include "proto/gen/ezcom.pb.h"
#include "zmq.h"

namespace ezcom {
namespace impl {

PublisherImpl::PublisherImpl(void* context,
                             const TransportType& transport_type) {
  node_type_ = NodeType::kPublisher;
  comm_mode_ = CommMode::kPubSub;
  transport_type_ = transport_type;
  // Create zmq socket
  if (context == nullptr) {
    throw InvalidParamException("Zmq context is nullptr");
  }
  context_ = context;
  socket_ = zmq_socket(context_, ZMQ_PUB);
}

PublisherImpl::PublisherImpl(const TransportType& transport_type)
    : PublisherImpl(zmq_ctx_new(), transport_type) {}

PublisherImpl::~PublisherImpl() {
  // destory zmq resources
  zmq_close(socket_);
  if (transport_type_ != TransportType::kZmqInproc) {
    zmq_ctx_term(context_);
  }
}

void PublisherImpl::Bind(const std::string& addr) {
  if (addr.empty()) {
    throw InvalidParamException("Invalid addr");
  }
  // bind socket
  int rc = -1;
  switch (transport_type_) {
    case TransportType::kZmqInproc: {
      rc = zmq_bind(socket_, ("inproc://" + addr).c_str());
    } break;
    case TransportType::kZmqIpc: {
      rc = zmq_bind(socket_, ("ipc:///tmp/" + addr).c_str());
    } break;
    case TransportType::kZmqTcp: {
      // 判断addr是否是ip地址
      if (addr.find(':') == std::string::npos) {
        throw InvalidParamException("Invalid ip address: " + addr);
      }
      rc = zmq_bind(socket_, ("tcp://" + addr).c_str());
    } break;
    default:
      throw InvalidParamException("Unknown transport type");
  }
  if (rc != 0) {
    throw ResourceException("Zmq bind failed");
  }
}

void PublisherImpl::Publish(const std::shared_ptr<Message>& msg,
                            const std::string& topic) {
  if (msg == nullptr) {
    throw InvalidParamException("Invalid msg is nullptr");
  }
  // ZMQ send with topic
  zmq_msg_t z_msg;
  zmq_msg_init_size(&z_msg,
                    topic.size() + msg->GetProtobufMessage()->ByteSizeLong());
  memcpy(zmq_msg_data(&z_msg), topic.c_str(), topic.size());
  msg->GetProtobufMessage()->SerializeToArray(
      (char*)zmq_msg_data(&z_msg) + topic.size(),
      msg->GetProtobufMessage()->ByteSizeLong());
  int rc = zmq_msg_send(&z_msg, socket_, 0);
  zmq_msg_close(&z_msg);
  if (rc == -1) {
    throw ResourceException("Zmq send failed");
  }
}

}  // namespace impl
}  // namespace ezcom
