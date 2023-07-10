#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include "ezcom/server.h"

namespace ezcom {
namespace impl {

class ServerImpl : public Server {
 public:
  ServerImpl(void* context, const TransportType& transport_type);
  ServerImpl(const TransportType& transport_type);
  ServerImpl(const ServerImpl&) = delete;
  ServerImpl& operator=(const ServerImpl&) = delete;
  ~ServerImpl();

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
