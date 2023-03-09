#include "async_requestor.h"

#include "pub_sub/async_requestor_impl.h"

namespace ezcom {

AsyncRequestor::AsyncRequestor(const std::string& address) {
  async_requestor_impl_ = std::make_shared<AsyncRequestorImpl>(address);
}

AsyncRequestor::~AsyncRequestor() { async_requestor_impl_ = nullptr; }

int AsyncRequestor::AsyncRequest(Message& message,
                                 std::function<void(const Message&)> callback) {
  return async_requestor_impl_->AsyncRequest(message, callback);
}

}  // namespace ezcom
