#include "async_responder.h"

#include "pub_sub/async_responder_impl.h"

namespace ezcom {

AsyncResponder::AsyncResponder(const std::string& address) {
  async_responder_impl_ = std::make_shared<AsyncResponderImpl>(address);
}

AsyncResponder::~AsyncResponder() { async_responder_impl_ = nullptr; }

void AsyncResponder::StartServer(
    std::function<Message(const Message&)> msg_callback) {
  async_responder_impl_->StartServer(msg_callback);
}

void AsyncResponder::StartServerForForgot(
    std::function<void(const Message&)> msg_callback) {
  std::function<Message(const Message&)> temp_func = [&](const Message& msg) {
    msg_callback(msg);
    return Message();
  };
  async_responder_impl_->StartServer(temp_func);
}

void AsyncResponder::StopServer() { async_responder_impl_->StopServer(); }

}  // namespace ezcom
