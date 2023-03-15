#pragma once
#include <atomic>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "message.h"

namespace ezcom {

class AsyncResponderImpl {
  using MsgCallback = std::function<Message(const Message&)>;

 public:
  AsyncResponderImpl(const std::string& server_addr);
  ~AsyncResponderImpl();

  void StartServer(MsgCallback msg_callback);
  void StopServer();

 private:
  void Init();
  void ServerLoop(MsgCallback msg_callback);

 private:
  void* ctx_{nullptr};
  void* rep_socket_{nullptr};
  std::string server_addr_;

  std::atomic_bool started_{false};
  std::shared_ptr<std::thread> server_thread_{nullptr};
};

}  // namespace ezcom
