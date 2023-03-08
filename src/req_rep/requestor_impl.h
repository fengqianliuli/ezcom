#pragma once

#include <string>

#include "message.h"

namespace ezcom {

class RequestorImpl final {
 public:
  RequestorImpl(const std::string& addr);
  ~RequestorImpl();
  bool ResetAddrAndReConnect(const std::string& addr);
  Message SyncRequest(const Message& message);

 private:
  void* ctx_;
  void* req_socket_;
  std::string addr_;
};

}  // namespace ezcom
