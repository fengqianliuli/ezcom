#pragma once

#include <atomic>
#include <future>

#include "ezcom/client.h"

namespace ezcom {

class ReqRepClientImpl : public Client {
 public:
  ReqRepClientImpl(void* context, const TransportType& transport_type);
  ReqRepClientImpl(const TransportType& transport_type);
  ReqRepClientImpl(const ReqRepClientImpl&) = delete;
  ReqRepClientImpl& operator=(const ReqRepClientImpl&) = delete;
  ~ReqRepClientImpl();
  void Connect(const std::string& addr,
               ConnectionCallback cb = nullptr) override;

  //  private:
 private:
  void* context_;
  void* socket_;
  void* monitor_socket_;
  std::future<void> monitor_future_;
  std::atomic_bool monitor_running_{false};
};

}  // namespace ezcom