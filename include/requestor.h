#pragma once

#include <functional>
#include <memory>

#include "message.h"

namespace ezcom {

class AsyncRequestorImpl;

class Requestor final {
  using Callback = std::function<void(const Message&)>;

 public:
  Requestor(std::string addr);
  ~Requestor();

  int RequestForgot(const Message& message);
  Message SyncRequest(const Message& message, int timeout_ms = -1);
  int AsyncRequest(const Message& message, Callback callback);

 private:
  std::shared_ptr<AsyncRequestorImpl> async_requestor_;
};

}  // namespace ezcom
