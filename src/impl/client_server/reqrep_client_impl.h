#pragma once

#include "ezcom/client.h"

namespace ezcom {

class ReqRepClientImpl : public Client {
 public:
  ReqRepClientImpl();
  ~ReqRepClientImpl();

  void Connect() override;

 private:
  
};

}  // namespace ezcom