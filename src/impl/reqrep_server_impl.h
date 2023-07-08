#pragma once

#include "ezcom/server.h"

namespace ezcom {

class ReqRepServerImpl : public Server {
 public:
  ReqRepServerImpl();
  ~ReqRepServerImpl();
};

}  // namespace ezcom