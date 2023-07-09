#pragma once

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

  void Bind(const std::string& addr) override;

 private:
  void* context_;
  void* socket_;
};

}  // namespace impl
}  // namespace ezcom
