#pragma once

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <set>

#include "common.h"
#include "message.h"

namespace ezcom {

class AsyncRequestorImpl;

class Requestor final {
  using Callback = std::function<void(const Message&)>;

 public:
  Requestor(TransportType transport_type, const std::string& server_addr);
  ~Requestor();

  void RequestForgot(const Message& message);
  Message SyncRequest(Message& message, int timeout_ms = -1);
  void AsyncRequest(const Message& message, Callback callback);

 private:
  std::shared_ptr<AsyncRequestorImpl> async_requestor_;
  Message response_;
  std::mutex mutex_;
  std::condition_variable cv_;
  bool done_{false};
  int64_t msg_id_{0};
  std::set<int64_t> msg_id_set_;
};

}  // namespace ezcom
