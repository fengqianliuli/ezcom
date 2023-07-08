#include "ezcom/client_factory.h"

#include "impl/reqrep_client_impl.h"

namespace ezcom {

std::unique_ptr<Client> ClientFactory::CreateClient(CommMode comm_mode) {
  switch (comm_mode) {
    case CommMode::kReqRep:
      return std::make_unique<ReqRepClientImpl>();
    case CommMode::kPubSub:
      throw std::runtime_error("Not support communication mode");
    default:
      throw std::runtime_error("Invalid communication mode");
  }
}

}  // namespace ezcom