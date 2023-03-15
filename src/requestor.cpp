#include "requestor.h"

#include <chrono>
#include <thread>

#include "req_rep/async_requestor_impl.h"

namespace ezcom {

Requestor::Requestor(TransportType transport_type, const std::string& server_addr) {
  std::string tmp_addr;
  switch (transport_type) {
    case TransportType::kTcp:
      if (server_addr.find(':') == std::string::npos) {
        throw std::invalid_argument("tcp address must be in format of ip:port");
      }
      tmp_addr = "tcp://" + server_addr;
      break;
    case TransportType::kIpc:
      if (server_addr.find(':') == std::string::npos) {
        tmp_addr = "ipc:///tmp/" + server_addr + ":0";
      } else {
        tmp_addr = "ipc:///tmp/" + server_addr;
      }
      break;
    default:
      break;
  }
  async_requestor_ = std::make_shared<AsyncRequestorImpl>(tmp_addr);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

Requestor::~Requestor() { async_requestor_ = nullptr; }

void Requestor::RequestForgot(const Message& message) {
  return async_requestor_->AsyncRequest(const_cast<Message&>(message), nullptr);
}

Message Requestor::SyncRequest(Message& message, int timeout_ms) {
  if (msg_id_ == std::numeric_limits<int64_t>::max()) {
    msg_id_ = 0;
  }
  message.SetMsgId(++msg_id_);
  auto callback = [this](const Message& msg) {
    if (msg_id_set_.find(msg.GetMsgId()) == msg_id_set_.end()) {
      return;
    }
    response_ = msg;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      done_ = true;
    }
    cv_.notify_one();
  };
  msg_id_set_.emplace(message.GetMsgId());
  async_requestor_->AsyncRequest(message, callback);

  std::unique_lock<std::mutex> lock(mutex_);
  if (timeout_ms < 0) {
    cv_.wait(lock, [this] { return done_; });
  } else {
    cv_.wait_for(lock, std::chrono::milliseconds(timeout_ms),
                [this] { return done_; });
  }
  msg_id_set_.erase(message.GetMsgId());
  return response_;
}

void Requestor::AsyncRequest(const Message& message, Callback callback) {
  return async_requestor_->AsyncRequest(const_cast<Message&>(message),
                                        callback);
}

}  // namespace ezcom
