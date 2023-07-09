#pragma once

#include <atomic>
#include <thread>
#include <memory>

#include "ezcom/server.h"

namespace ezcom {
namespace impl {

class ReqRepServerImpl : public Server {
 public:
  ReqRepServerImpl(void* context, const TransportType& transport_type);
  ReqRepServerImpl(const TransportType& transport_type);
  ReqRepServerImpl(const ReqRepServerImpl&) = delete;
  ReqRepServerImpl& operator=(const ReqRepServerImpl&) = delete;
  ~ReqRepServerImpl();

  void Bind(const std::string& addr, const MessageHandler& handler) override;

 private:
  void MsgHandle(const MessageHandler& handler);

 private:
  void* context_;
  void* socket_;
  std::shared_ptr<std::thread> msg_handle_thread_;
  std::atomic_bool msg_handle_running_{false};
};

}  // namespace impl
}  // namespace ezcom
