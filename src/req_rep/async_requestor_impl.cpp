#include "async_requestor_impl.h"

#include <errno.h>
#include <stdexcept>
#include "proto/gen/ezcom.pb.h"
#include "zmq.h"

namespace ezcom {

AsyncRequestorImpl::AsyncRequestorImpl(const std::string& server_addr)
    : server_addr_(server_addr) {
  Init();
}

AsyncRequestorImpl::~AsyncRequestorImpl() {
  zmq_close(req_socket_);
  zmq_ctx_term(ctx_);
  started_.store(false);
  if (send_thread_->joinable()) {
    send_thread_->join();
  }
}

void AsyncRequestorImpl::Init() {
  std::cout << "Requestor: server addr = " << server_addr_ << std::endl;
  ctx_ = zmq_ctx_new();
  req_socket_ = zmq_socket(ctx_, ZMQ_REQ);
  if (zmq_connect(req_socket_, server_addr_.c_str()) != 0) {
    throw std::runtime_error("AsyncRequestor: zmq_connect failed");
  };

  queue_ = std::make_shared<ThreadSafeQueue<std::pair<Message, Callback>>>();

  started_.store(true);
  send_thread_ =
      std::make_shared<std::thread>(&AsyncRequestorImpl::SendLoop, this);
}

void AsyncRequestorImpl::AsyncRequest(Message& message, Callback callback) {
  if (msg_id_ == std::numeric_limits<int64_t>::max()) {
    msg_id_ = 0;
  }
  message.SetMsgId(++msg_id_);
  queue_->Enqueue({message, callback});
}

void AsyncRequestorImpl::SendLoop() {
  while (started_) {
    std::pair<Message, Callback> pair;
    if (!queue_->WaitDequeue(&pair)) {
      continue;
    }
    Message& message = pair.first;
    Callback& callback = pair.second;
    zmq_msg_t msg;
    zmq_msg_init_size(&msg, message.proto_msg_->ByteSizeLong());
    message.proto_msg_->SerializeToArray(zmq_msg_data(&msg),
                                         message.proto_msg_->ByteSizeLong());
    int rc = zmq_msg_send(&msg, req_socket_, 0);
    zmq_msg_close(&msg);
    if (rc == -1) {
      std::cout << "AsyncRequestor: zmq_msg_send failed, errno = " << errno
                << std::endl;
      continue;
    }
    zmq_msg_t reply;
    zmq_msg_init(&reply);
    rc = zmq_msg_recv(&reply, req_socket_, 0);
    if (rc == -1) {
      std::cout << "AsyncRequestor: zmq_msg_recv failed, errno = " << errno
                << std::endl;
      continue;
    }
    Message reply_msg;
    reply_msg.proto_msg_->ParseFromArray(zmq_msg_data(&reply),
                                         zmq_msg_size(&reply));
    zmq_msg_close(&reply);
    if (callback != nullptr) {
      callback(reply_msg);
    }
  }
}

}  // namespace ezcom
