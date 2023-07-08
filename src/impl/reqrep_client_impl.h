#pragma once

#include "ezcom/client.h"

namespace ezcom {

class ReqRepClientImpl : public Client {
 public:
  ReqRepClientImpl(const void* context, const TransportType& transport_type);
  ReqRepClientImpl(const TransportType& transport_type);
  ReqRepClientImpl(const ReqRepClientImpl&) = delete;
  ReqRepClientImpl& operator=(const ReqRepClientImpl&) = delete;
  ~ReqRepClientImpl();
  void Connect(const std::string& addr,
               ConnectionCallback cb = nullptr) override;

 private:
  void* context_;
  void* socket_;
};

}  // namespace ezcom