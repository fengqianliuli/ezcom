#include "responder.h"

#include <chrono>
#include <thread>

#include "pub_sub/async_responder_impl.h"

namespace ezcom {

Responder::Responder(std::string addr) {
  async_responder_ = std::make_shared<AsyncResponderImpl>(addr);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

Responder::~Responder() { async_responder_ = nullptr; }

void Responder::StartServer(MsgCallback msg_callback) {
  async_responder_->StartServer(msg_callback);
}

void Responder::StartServerForgot(MsgCallbackForgot msg_callback) {
  async_responder_->StartServer([msg_callback](const Message& msg) -> Message {
    msg_callback(msg);
    return Message();
  });
}

void Responder::StopServer() { async_responder_->StopServer(); }

}  // namespace ezcom
