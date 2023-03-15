#include "requestor.h"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "pub_sub/async_requestor_impl.h"

namespace ezcom {

Requestor::Requestor(TransportType transport_type, std::string addr) {
  switch (transport_type) {
    case TransportType::kTcp:
      if (addr.find(':') == std::string::npos) {
        throw std::invalid_argument("tcp address must be in format of ip:port");
      }
      addr = "tcp://" + addr;
      break;
    case TransportType::kIpc:
      if (addr.find(':') == std::string::npos) {
        addr = "ipc:///tmp/" + addr + ":0";
      } else {
        addr = "ipc:///tmp/" + addr;
      }
      break;
    default:
      break;
  }
  async_requestor_ = std::make_shared<AsyncRequestorImpl>(addr);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

Requestor::Requestor(TransportType transport_type, std::string local_addr,
                     std::string remote_addr) {
  switch (transport_type) {
    case TransportType::kTcp:
      if (local_addr.find(':') == std::string::npos || remote_addr.find(':') == std::string::npos) {
        throw std::invalid_argument("tcp address must be in format of ip:port");
      }
      local_addr = "tcp://" + local_addr;
      remote_addr = "tcp://" + remote_addr;
      break;
    case TransportType::kIpc:
      local_addr = "ipc:///tmp/" + local_addr;
      remote_addr = "ipc:///tmp/" + remote_addr;
      break;
    default:
      break;
  }
  async_requestor_ =
      std::make_shared<AsyncRequestorImpl>(local_addr, remote_addr);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

Requestor::~Requestor() { async_requestor_ = nullptr; }

int Requestor::RequestForgot(const Message& message) {
  return async_requestor_->AsyncRequest(const_cast<Message&>(message), nullptr);
}

Message Requestor::SyncRequest(const Message& message, int timeout_ms) {
  Message response;
  std::mutex mutex;
  std::condition_variable cv;
  bool done = false;
  auto callback = [&response, &mutex, &cv, &done](const Message& msg) {
    response = msg;
    {
      std::lock_guard<std::mutex> lock(mutex);
      done = true;
    }
    cv.notify_one();
  };
  int rc =
      async_requestor_->AsyncRequest(const_cast<Message&>(message), callback);
  std::unique_lock<std::mutex> lock(mutex);
  if (timeout_ms < 0) {
    cv.wait(lock, [&done] { return done; });
  } else {
    cv.wait_for(lock, std::chrono::milliseconds(timeout_ms),
                [&done] { return done; });
  }
  return response;
}

int Requestor::AsyncRequest(const Message& message, Callback callback) {
  return async_requestor_->AsyncRequest(const_cast<Message&>(message),
                                        callback);
}

}  // namespace ezcom
