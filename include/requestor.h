#pragma once

#include <memory>
#include "message.h"

namespace ezcom {

class RequestorImpl;

class Requestor final {
 public:
  Requestor(const std::string& address);
  ~Requestor();
  Requestor(const Requestor&) = delete;
  Requestor& operator=(const Requestor&) = delete;
  Requestor(Requestor&&) = delete;
  Requestor& operator=(Requestor&&) = delete;

  bool ResetAddrAndReConnect(const std::string& addr);
  Message SyncRequest(const Message& message);


 private:
  std::shared_ptr<RequestorImpl> requestor_impl_{nullptr};

};

}  // namespace ezcom
