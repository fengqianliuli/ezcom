#include "responder_impl.h"

#include <stdexcept>

#include "errno.h"
#include "proto/gen/ezcom.pb.h"
#include "zmq.h"

namespace ezcom {

ResponderImpl::ResponderImpl(const std::string& addr) : addr_(addr) {
  ctx_ = zmq_ctx_new();
  rep_socket_ = zmq_socket(ctx_, ZMQ_REP);
  if (zmq_bind(rep_socket_, addr_.c_str()) != 0) {
    std::string err_msg = "zmq_bind failed: ";
    err_msg.append(zmq_strerror(errno));
    throw std::runtime_error(err_msg);
  }
}

ResponderImpl::~ResponderImpl() {
  zmq_close(rep_socket_);
  zmq_ctx_term(ctx_);
  this->StopServer();
  if (server_thread_->joinable()) {
    server_thread_->join();
  }
}

bool ResponderImpl::ResetAddrAndRebind(const std::string& addr) {
  if (zmq_unbind(rep_socket_, addr_.c_str()) != 0) {
    return false;
  }
  if (zmq_bind(rep_socket_, addr.c_str()) != 0) {
    return false;
  }
  addr_ = addr;
  return true;
}

void ResponderImpl::StartServer(MsgCallback msg_callback) {
  if (started_) {
    return;
  }
  started_ = true;
  server_thread_ = std::make_shared<std::thread>(&ResponderImpl::ServerLoop,
                                                 this, msg_callback);
}

void ResponderImpl::StopServer() { started_ = false; }

void ResponderImpl::ServerLoop(MsgCallback msg_callback) {
  while (started_) {
    zmq_msg_t request;
    zmq_msg_init(&request);
    if (zmq_msg_recv(&request, rep_socket_, 0) < 0) {
      // when response obj is destroyed, zmq_msg_recv will fail, but it's not an
      // error throw std::runtime_error("zmq_msg_recv failed");
      continue;
    }
    Message request_msg;
    request_msg.proto_msg_->ParseFromArray(zmq_msg_data(&request),
                                           zmq_msg_size(&request));
    zmq_msg_close(&request);

    Message response_msg = msg_callback(request_msg);

    zmq_msg_t reply;
    zmq_msg_init_size(&reply, response_msg.proto_msg_->ByteSizeLong());
    response_msg.proto_msg_->SerializeToArray(zmq_msg_data(&reply),
                                              zmq_msg_size(&reply));
    if (zmq_msg_send(&reply, rep_socket_, 0) < 0) {
      throw std::runtime_error("zmq_msg_send failed");
    }
    zmq_msg_close(&reply);
  }
}

}  // namespace ezcom
