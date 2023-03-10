#include "requestor.h"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "pub_sub/async_requestor_impl.h"

namespace ezcom {

Requestor::Requestor(std::string addr) {
  async_requestor_ = std::make_shared<AsyncRequestorImpl>(addr);
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
