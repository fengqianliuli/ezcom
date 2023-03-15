#pragma once

#include <functional>
#include <memory>

#include "message.h"
#include "common.h"

namespace ezcom {

class AsyncResponderImpl;

class Responder final {
  using MsgCallback = std::function<Message(const Message&)>;
  using MsgCallbackForgot = std::function<void(const Message&)>;

 public:
  Responder(TransportType transport_type, std::string addr);
  Responder(TransportType transport_type, std::string local_addr,
            std::string remote_addr);
  ~Responder();

  void StartServer(MsgCallback msg_callback);
  void StartServerForgot(MsgCallbackForgot msg_callback);
  void StopServer();

 private:
  std::shared_ptr<AsyncResponderImpl> async_responder_;
};

}  // namespace ezcom
