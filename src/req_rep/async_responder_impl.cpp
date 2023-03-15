#include "async_responder_impl.h"

#include <stdexcept>

#include "proto/gen/ezcom.pb.h"
#include "zmq.h"

namespace ezcom {

AsyncResponderImpl::AsyncResponderImpl(const std::string& server_addr)
    : server_addr_(server_addr) {
  Init();
}

AsyncResponderImpl::~AsyncResponderImpl() {
  zmq_close(rep_socket_);
  zmq_ctx_term(ctx_);
  this->StopServer();
  if (server_thread_->joinable()) {
    server_thread_->join();
  }
}

void AsyncResponderImpl::Init() {
  std::cout << "Responder: server addr = " << server_addr_ << std::endl;
  ctx_ = zmq_ctx_new();
  rep_socket_ = zmq_socket(ctx_, ZMQ_REP);

  if (zmq_bind(rep_socket_, server_addr_.c_str()) != 0) {
    throw std::runtime_error("AsyncResponder: zmq_bind failed");
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
    int rc = zmq_msg_recv(&msg, rep_socket_, 0);
    if (rc == -1) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      continue;
    }
    Message message;
    message.proto_msg_->ParseFromArray(zmq_msg_data(&msg), zmq_msg_size(&msg));
    zmq_msg_close(&msg);

    Message response = msg_callback(message);

    response.SetMsgId(message.GetMsgId());
    zmq_msg_t response_msg;
    zmq_msg_init_size(&response_msg, response.proto_msg_->ByteSizeLong());
    response.proto_msg_->SerializeToArray(zmq_msg_data(&response_msg),
                                          response.proto_msg_->ByteSizeLong());
    rc = zmq_msg_send(&response_msg, rep_socket_, 0);
    zmq_msg_close(&response_msg);
  }
}

}  // namespace ezcom
