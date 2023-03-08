#include "responder.h"
#include "req_rep/responder_impl.h"

namespace ezcom {

Responder::Responder(const std::string& address) {
  responder_impl_ = std::make_shared<ResponderImpl>(address);
}

Responder::~Responder() { responder_impl_ = nullptr; }

bool Responder::ResetAddrAndRebind(const std::string& addr) {
  return responder_impl_->ResetAddrAndRebind(addr);
}

void Responder::StartServer(std::function<Message(const Message&)> msg_callback) {
  responder_impl_->StartServer(msg_callback);
}

void Responder::StopServer() { responder_impl_->StopServer(); }

}  // namespace ezcom
