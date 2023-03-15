#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <atomic>

#include "message.h"

namespace ezcom {

class AsyncRequestorImpl {
  using Callback = std::function<void(const Message&)>;

 public:
  AsyncRequestorImpl(const std::string& addr);
  AsyncRequestorImpl(const std::string& local_addr, const std::string& remote_addr);
  ~AsyncRequestorImpl();

  int AsyncRequest(Message& message, Callback callback);

 private:
  void Init();
  void ReceiveLoop();

 private:
  void* ctx_{nullptr};
  void* pub_socket_{nullptr};
  void* sub_socket_{nullptr};
  std::string pub_addr_;
  std::string sub_addr_;
  std::shared_ptr<std::map<int64_t, Callback>> callback_map_{nullptr};
  std::shared_ptr<std::thread> receive_thread_{nullptr};
  std::atomic_bool started_{false};
  int64_t msg_id_{0};
};

}  // namespace ezcom
