#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "message.h"

namespace ezcom {

class ResponderImpl final {
  using MsgCallback = std::function<Message(const Message&)>;

 public:
  ResponderImpl(const std::string& addr);
  ~ResponderImpl();
  bool ResetAddrAndRebind(const std::string& addr);
  void StartServer(MsgCallback msg_callback);
  void StopServer();

 private:
  void ServerLoop(MsgCallback msg_callback);

 private:
  void* ctx_{nullptr};
  void* rep_socket_{nullptr};
  std::string addr_;

  std::atomic_bool started_{false};
  std::shared_ptr<std::thread> server_thread_{nullptr};
};

}  // namespace ezcom
