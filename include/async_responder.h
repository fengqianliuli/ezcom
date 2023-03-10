#pragma once

#include <functional>
#include <memory>
#include <string>

#include "message.h"

namespace ezcom {

class AsyncResponderImpl;

class AsyncResponder final {
 public:
  AsyncResponder(const std::string& address);
  ~AsyncResponder();
  AsyncResponder(const AsyncResponder&) = delete;
  AsyncResponder& operator=(const AsyncResponder&) = delete;
  AsyncResponder(AsyncResponder&&) = delete;
  AsyncResponder& operator=(AsyncResponder&&) = delete;

  void StartServer(std::function<Message(const Message&)> msg_callback);
  void StartServerForForgot(std::function<void(const Message&)> msg_callback);
  void StopServer();

 private:
  std::shared_ptr<AsyncResponderImpl> async_responder_impl_{nullptr};
};

}  // namespace ezcom
