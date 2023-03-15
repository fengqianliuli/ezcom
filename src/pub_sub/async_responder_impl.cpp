#include "async_responder_impl.h"

#include <stdexcept>

#include "proto/gen/ezcom.pb.h"
#include "zmq.h"

namespace ezcom {

AsyncResponderImpl::AsyncResponderImpl(const std::string& addr)
    : sub_addr_(addr) {
  // pub_addr_ = sub_addr_ port + 1
  pub_addr_ =
      sub_addr_.substr(0, sub_addr_.find_last_of(":") + 1) +
      std::to_string(
          std::stoi(sub_addr_.substr(sub_addr_.find_last_of(":") + 1)) + 1);
  Init();
}

AsyncResponderImpl::AsyncResponderImpl(const std::string& local_addr,
                                       const std::string& remote_addr)
    : pub_addr_(local_addr), sub_addr_(remote_addr) {
  Init();
}

AsyncResponderImpl::~AsyncResponderImpl() {
  zmq_close(pub_socket_);
  zmq_close(sub_socket_);
  zmq_ctx_term(ctx_);
  this->StopServer();
  if (server_thread_->joinable()) {
    server_thread_->join();
  }
}

void AsyncResponderImpl::Init() {
  std::cout << "Responder: local addr = " << pub_addr_ << std::endl;
  std::cout << "Responder: remote addr = " << sub_addr_ << std::endl;
  ctx_ = zmq_ctx_new();
  pub_socket_ = zmq_socket(ctx_, ZMQ_PUB);
  sub_socket_ = zmq_socket(ctx_, ZMQ_SUB);

  if (zmq_bind(pub_socket_, pub_addr_.c_str()) != 0) {
    throw std::runtime_error("AsyncResponder: zmq_bind failed");
  }
  if (zmq_connect(sub_socket_, sub_addr_.c_str()) != 0) {
    throw std::runtime_error("AsyncResponder: zmq_connect failed");
  }
  if (zmq_setsockopt(sub_socket_, ZMQ_SUBSCRIBE, "", 0) != 0) {
    throw std::runtime_error("AsyncResponder: zmq_setsockopt failed");
  }
}

void AsyncResponderImpl::StartServer(MsgCallback msg_callback) {
  if (started_.load()) {
    return;
  }
  started_.store(true);
  server_thread_ = std::make_shared<std::thread>(
      &AsyncResponderImpl::ServerLoop, this, msg_callback);
}

void AsyncResponderImpl::StopServer() {
  if (!started_.load()) {
    return;
  }
  started_.store(false);
}

void AsyncResponderImpl::ServerLoop(MsgCallback msg_callback) {
  while (started_.load()) {
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    int rc = zmq_msg_recv(&msg, sub_socket_, 0);
    if (rc == -1) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      continue;
    }
    ProtobufMessage proto_msg;
    proto_msg.ParseFromArray(zmq_msg_data(&msg), zmq_msg_size(&msg));
    zmq_msg_close(&msg);
    Message message;
    message.proto_msg_ = std::make_shared<ProtobufMessage>(proto_msg);
    Message response = msg_callback(message);
    response.SetMsgId(message.GetMsgId());
    zmq_msg_t response_msg;
    zmq_msg_init_size(&response_msg, response.proto_msg_->ByteSizeLong());
    response.proto_msg_->SerializeToArray(zmq_msg_data(&response_msg),
                                          response.proto_msg_->ByteSizeLong());
    rc = zmq_msg_send(&response_msg, pub_socket_, 0);
    zmq_msg_close(&response_msg);
  }
}

}  // namespace ezcom
