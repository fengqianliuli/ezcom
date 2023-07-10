#pragma once

#include <atomic>
#include <future>
#include <thread>
#include <map>
#include <set>

#include "ezcom/client.h"
#include "utils/thread_safe_queue.h"

namespace ezcom {
namespace impl {

using ReturnMsgCb = std::function<void(const std::shared_ptr<Message>&)>;

struct MsgPack {
  std::shared_ptr<Message> req_message;
  ReturnMsgCb return_msg_cb;
};

class ReqRepClientImpl : public Client {
 public:
  ReqRepClientImpl(const TransportType& transport_type);
  ReqRepClientImpl(void* context, const TransportType& transport_type);
  ReqRepClientImpl(const ReqRepClientImpl&) = delete;
  ReqRepClientImpl& operator=(const ReqRepClientImpl&) = delete;
  ~ReqRepClientImpl();
  void Connect(const std::string& addr,
               const ConnectionCallback& conn_cb = nullptr) override;
  Result SyncRequest(const std::shared_ptr<Message>& req_message,
                     int timeout_ms = -1) override;
  void AsyncRequest(const std::shared_ptr<Message>& req_message,
                    const ResultCallback& result_cb,
                    int timeout_ms = -1) override;

 private:
  void MsgSendLoop();

 private:
  void* context_;
  void* socket_;
  void* monitor_socket_;
  std::future<void> monitor_future_;
  std::atomic_bool monitor_running_{false};

  std::atomic_uint64_t msg_id_{1};
  std::shared_ptr<std::set<uint64_t>> msg_id_set_;
  std::shared_ptr<utils::ThreadSafeQueue<impl::MsgPack>> msg_queue_;
  std::shared_ptr<std::thread> msg_send_thread_;
  using PromiseMap =
      std::map<int, std::pair<std::promise<const std::shared_ptr<Message>&>,
                              std::future<const std::shared_ptr<Message>&>>>;
  std::shared_ptr<PromiseMap> promise_map_;
};

}  // namespace impl
}  // namespace ezcom