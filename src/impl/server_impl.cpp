#include "server_impl.h"

#include "ezcom/exception.h"
#include "proto/gen/ezcom.pb.h"
#include "zmq.h"

namespace ezcom {
namespace impl {

ServerImpl::ServerImpl(void* context, const TransportType& transport_type) {
  node_type_ = NodeType::kServer;
  comm_mode_ = CommMode::kReqRep;
  transport_type_ = transport_type;
  // Create zmq socket
  if (context == nullptr) {
    throw InvalidParamException("Zmq context is nullptr");
  }
  context_ = context;
  socket_ = zmq_socket(context_, ZMQ_REP);
}

ServerImpl::ServerImpl(const TransportType& transport_type)
    : ServerImpl(zmq_ctx_new(), transport_type) {}

ServerImpl::~ServerImpl() {
  // stop message handle thread
  msg_handle_running_ = false;
  if (msg_handle_thread_->joinable()) {
    msg_handle_thread_->join();
  }

  // destory zmq resources
  zmq_close(socket_);
  if (transport_type_ != TransportType::kZmqInproc) {
    zmq_ctx_term(context_);
  }
}

void ServerImpl::Bind(const std::string& addr, const MessageHandler& handler) {
  static std::atomic_bool bind{false};
  if (bind) {
    throw AlreadyDoneException("Server has already been bound");
  }
  if (addr.empty()) {
    throw InvalidParamException("Invalid addr");
  }
  if (handler == nullptr) {
    throw InvalidParamException("Invalid handler function");
  }
  if (msg_handle_running_) {
    throw ResourceException("Message handle thread already is running");
  }

  int rc = -1;
  // set socketopt
  rc = zmq_setsockopt(socket_, ZMQ_RCVTIMEO, &kZmqRcvTimeout,
                      sizeof(kZmqRcvTimeout));
  if (rc != 0) {
    throw ResourceException("Zmq setsockopt failed");
  }

  // bind socket
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
  bind = true;

  // start message handle thread
  msg_handle_running_ = true;
  msg_handle_thread_ = std::make_shared<std::thread>(
      std::bind(&ServerImpl::MsgHandle, this, handler));
}

void ServerImpl::MsgHandle(const MessageHandler& handler) {
  while (msg_handle_running_) {
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
    message->GetProtobufMessage()->ParseFromArray(zmq_msg_data(&z_msg),
                                                  zmq_msg_size(&z_msg));
    zmq_msg_close(&z_msg);

    auto response = handler(message);
    response->SetMsgId(message->GetMsgId());
    zmq_msg_t z_rep_msg;
    zmq_msg_init_size(&z_rep_msg,
                      response->GetProtobufMessage()->ByteSizeLong());
    response->GetProtobufMessage()->SerializeToArray(
        zmq_msg_data(&z_rep_msg),
        response->GetProtobufMessage()->ByteSizeLong());
    zmq_msg_send(&z_rep_msg, socket_, 0);
    zmq_msg_close(&z_rep_msg);
  }
}

}  // namespace impl
}  // namespace ezcom
