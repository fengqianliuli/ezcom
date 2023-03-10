#include "async_requestor_impl.h"

#include <errno.h>
#include <stdexcept>

#include "proto/gen/ezcom.pb.h"
#include "zmq.h"

namespace ezcom {

AsyncRequestorImpl::AsyncRequestorImpl(const std::string& addr)
    : pub_addr_(addr) {
  // sub_addr_ = pub_addr_ port + 1
  sub_addr_ =
      pub_addr_.substr(0, pub_addr_.find_last_of(":") + 1) +
      std::to_string(
          std::stoi(pub_addr_.substr(pub_addr_.find_last_of(":") + 1)) + 1);
  ctx_ = zmq_ctx_new();
  pub_socket_ = zmq_socket(ctx_, ZMQ_PUB);
  sub_socket_ = zmq_socket(ctx_, ZMQ_SUB);

  if (zmq_bind(pub_socket_, pub_addr_.c_str()) != 0) {
    throw std::runtime_error("AsyncRequestor: zmq_bind failed");
  }
  if (zmq_connect(sub_socket_, sub_addr_.c_str()) != 0) {
    throw std::runtime_error("AsyncRequestor: zmq_connect failed");
  };
  if (zmq_setsockopt(sub_socket_, ZMQ_SUBSCRIBE, "", 0) != 0) {
    throw std::runtime_error("AsyncRequestor: zmq_setsockopt failed");
  }
  callback_map_ = std::make_shared<std::map<int64_t, Callback>>();
  started_.store(true);
  receive_thread_ =
      std::make_shared<std::thread>(&AsyncRequestorImpl::ReceiveLoop, this);
}

AsyncRequestorImpl::~AsyncRequestorImpl() {
  zmq_close(pub_socket_);
  zmq_close(sub_socket_);
  zmq_ctx_term(ctx_);
  started_.store(false);
  if (receive_thread_->joinable()) {
    receive_thread_->join();
  }
}

int AsyncRequestorImpl::AsyncRequest(Message& message,
                                     Callback callback) {
  if (msg_id_ == std::numeric_limits<int64_t>::max()) {
    msg_id_ = 0;
  }
  message.SetMsgId(++msg_id_);
  zmq_msg_t msg;
  zmq_msg_init_size(&msg, message.proto_msg_->ByteSizeLong());
  message.proto_msg_->SerializeToArray(zmq_msg_data(&msg),
                                       message.proto_msg_->ByteSizeLong());
  int rc = zmq_msg_send(&msg, pub_socket_, 0);
  zmq_msg_close(&msg);
  if (callback != nullptr) {
    callback_map_->insert({message.GetMsgId(), std::move(callback)});
  }
  return rc;
}

void AsyncRequestorImpl::ReceiveLoop() {
  while (started_) {
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
    auto iter = callback_map_->find(proto_msg.msg_id());
    if (iter != callback_map_->end()) {
      Message message;
      message.proto_msg_ = std::make_shared<ProtobufMessage>(proto_msg);
      iter->second(message);
      callback_map_->erase(iter);
    }
  }
}

}  // namespace ezcom
