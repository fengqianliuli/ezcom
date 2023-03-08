#include "requestor.h"

#include "req_rep/requestor_impl.h"

namespace ezcom {

Requestor::Requestor(const std::string& address) {
  requestor_impl_ = std::make_shared<RequestorImpl>(address);
}

Requestor::~Requestor() { requestor_impl_ = nullptr; }

bool Requestor::ResetAddrAndReConnect(const std::string& addr) {
  return requestor_impl_->ResetAddrAndReConnect(addr);
}

Message Requestor::SyncRequest(const Message& message) {
  return requestor_impl_->SyncRequest(message);
}

}  // namespace ezcom
