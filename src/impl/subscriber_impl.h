#pragma once

#include <atomic>
#include <thread>

#include "ezcom/subscriber.h"

namespace ezcom {
namespace impl {

class SubscriberImpl : public Subscriber {
 public:
  SubscriberImpl(void* context, const TransportType& transport_type);
  SubscriberImpl(const TransportType& transport_type);
  SubscriberImpl(const SubscriberImpl&) = delete;
  SubscriberImpl& operator=(const SubscriberImpl&) = delete;
  ~SubscriberImpl();

  void Subscribe(const std::string& addr, const MsgCallback& msg_cb,
                 const std::string& topic = "") override;

 private:
  void RecvThread(const MsgCallback& msg_cb);

 private:
  void* context_;
  void* socket_;
  std::string topic_{""};
  std::atomic_bool recv_running_{false};
  std::shared_ptr<std::thread> recv_thread_;
};

}  // namespace impl
}  // namespace ezcom
