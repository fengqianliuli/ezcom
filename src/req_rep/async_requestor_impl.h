#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <atomic>

#include "message.h"
#include "utils/thread_safe_queue.h"

namespace ezcom {

class AsyncRequestorImpl {
  using Callback = std::function<void(const Message&)>;

 public:
  AsyncRequestorImpl(const std::string& server_addr);
  ~AsyncRequestorImpl();

  void AsyncRequest(Message& message, Callback callback);

 private:
  void Init();
  void SendLoop();

 private:
  void* ctx_{nullptr};
  void* req_socket_{nullptr};
  std::string server_addr_;

  int64_t msg_id_{0};
  std::shared_ptr<ThreadSafeQueue<std::pair<Message, Callback>>> queue_{nullptr};
  std::shared_ptr<std::thread> send_thread_{nullptr};
  std::atomic_bool started_{false};
};

}  // namespace ezcom
