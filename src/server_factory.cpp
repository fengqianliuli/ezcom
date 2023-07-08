#include "ezcom/server_factory.h"

#include "impl/pubsub_server_impl.h"
#include "impl/reqrep_server_impl.h"

namespace ezcom {

std::unique_ptr<Server> ServerFactory::CreateServer(CommMode comm_mode) {
  switch (comm_mode) {
    case CommMode::kReqRep:
      return std::make_unique<ReqRepServerImpl>();
      break;
    case CommMode::kPubSub:
      return std::make_unique<PubsubServerImpl>();
      break;

    default:
      throw std::runtime_error("Invalid communication mode");
      break;
  }
}

}  // namespace ezcom