#pragma once

#include <memory>

#include "server.h"
#include "types.h"

namespace ezcom {

class ServerFactory {
 public:
  static std::unique_ptr<Server> CreateServer(CommMode comm_mode);
};

}  // namespace ezcom