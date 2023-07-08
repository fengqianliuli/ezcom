#include "ezcom/client_factory.h"

#include "impl/pubsub_client_impl.h"
#include "impl/reqrep_client_impl.h"

namespace ezcom {

std::unique_ptr<Client> ClientFactory::CreateClient(CommMode comm_mode) {
  switch (comm_mode) {
    case CommMode::kReqRep:
      return std::make_unique<ReqRepClientImpl>();
      break;
    case CommMode::kPubSub:
      return std::make_unique<PubsubClientImpl>();
      break;

    default:
      throw std::runtime_error("Invalid communication mode");
      break;
  }
}

}  // namespace ezcom