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
  AsyncResponderImpl(const std::string& addr);
  ~AsyncResponderImpl();

  void StartServer(MsgCallback msg_callback);
  void StopServer();

 private:
  void ServerLoop(MsgCallback msg_callback);

 private:
  void* ctx_{nullptr};
  void* pub_socket_{nullptr};
  void* sub_socket_{nullptr};
  std::string pub_addr_;
  std::string sub_addr_;

  std::atomic_bool started_{false};
  std::shared_ptr<std::thread> server_thread_{nullptr};
};

}  // namespace ezcom
