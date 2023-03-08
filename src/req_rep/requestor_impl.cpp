#include "requestor_impl.h"

#include <stdexcept>

#include "proto/gen/ezcom.pb.h"
#include "zmq.h"

namespace ezcom {

RequestorImpl::RequestorImpl(const std::string& addr) : addr_(addr) {
  ctx_ = zmq_ctx_new();
  req_socket_ = zmq_socket(ctx_, ZMQ_REQ);
  if (zmq_connect(req_socket_, addr_.c_str()) != 0) {
    throw std::runtime_error("zmq_connect failed");
  }
}

RequestorImpl::~RequestorImpl() {
  zmq_close(req_socket_);
  zmq_ctx_term(ctx_);
}

bool RequestorImpl::ResetAddrAndReConnect(const std::string& addr) {
  if (zmq_disconnect(req_socket_, addr_.c_str()) != 0) {
    return false;
  }
  if (zmq_connect(req_socket_, addr.c_str()) != 0) {
    return false;
  }
  addr_ = addr;
  return true;
}

Message RequestorImpl::SyncRequest(const Message& message) {
  Message response;
  zmq_msg_t request;
  zmq_msg_init_size(&request, message.proto_msg_->ByteSizeLong());
  message.proto_msg_->SerializeToArray(zmq_msg_data(&request),
                                       zmq_msg_size(&request));
  if (zmq_msg_send(&request, req_socket_, 0) < 0) {
    throw std::runtime_error("zmq_msg_send failed");
  }
  zmq_msg_close(&request);

  zmq_msg_t reply;
  zmq_msg_init(&reply);
  if (zmq_msg_recv(&reply, req_socket_, 0) < 0) {
    throw std::runtime_error("zmq_msg_recv failed");
  }
  response.proto_msg_->ParseFromArray(zmq_msg_data(&reply),
                                      zmq_msg_size(&reply));
  zmq_msg_close(&reply);

  return response;
}

}  // namespace ezcom
