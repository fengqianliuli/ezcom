#pragma once

#include "ezcom/server.h"

namespace ezcom {

class PubsubServerImpl : public Server {
 public:
  PubsubServerImpl();
  ~PubsubServerImpl();
};

}  // namespace ezcom