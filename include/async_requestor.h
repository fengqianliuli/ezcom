#pragma once

#include <functional>
#include <memory>

#include "message.h"

namespace ezcom {

class AsyncRequestorImpl;

class AsyncRequestor final {
 public:
  AsyncRequestor(const std::string& address);
  ~AsyncRequestor();
  AsyncRequestor(const AsyncRequestor&) = delete;
  AsyncRequestor& operator=(const AsyncRequestor&) = delete;
  AsyncRequestor(AsyncRequestor&&) = delete;
  AsyncRequestor& operator=(AsyncRequestor&&) = delete;

  int AsyncRequest(Message& message,
                   std::function<void(const Message&)> callback);

 private:
  std::shared_ptr<AsyncRequestorImpl> async_requestor_impl_{nullptr};
};

}  // namespace ezcom
