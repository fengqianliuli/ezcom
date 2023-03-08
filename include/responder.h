#pragma once

#include <string>
#include <memory>
#include <functional>

#include "message.h"

namespace ezcom {

class ResponderImpl;

class Responder final {
 public:
  Responder(const std::string& address);
  ~Responder();
  Responder(const Responder&) = delete;
  Responder& operator=(const Responder&) = delete;
  Responder(Responder&&) = delete;
  Responder& operator=(Responder&&) = delete;

  bool ResetAddrAndRebind(const std::string& addr);
  void StartServer(std::function<Message(const Message&)> msg_callback);
  void StopServer();

 private:
  std::shared_ptr<ResponderImpl> responder_impl_{nullptr};
};

} // namespace ezcom
