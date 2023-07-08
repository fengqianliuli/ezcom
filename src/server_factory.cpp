#include "ezcom/server_factory.h"

#include "impl/reqrep_server_impl.h"

namespace ezcom {

std::unique_ptr<Server> ServerFactory::CreateServer(CommMode comm_mode) {
  switch (comm_mode) {
    case CommMode::kReqRep:
      return std::make_unique<ReqRepServerImpl>();
    case CommMode::kPubSub:
      throw std::runtime_error("Not support communication mode");
    default:
      throw std::runtime_error("Invalid communication mode");
  }
}

}  // namespace ezcom