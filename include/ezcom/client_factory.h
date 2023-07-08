#pragma once

#include <memory>

#include "client.h"
#include "types.h"

namespace ezcom {

class ClientFactory {
 public:
  static std::unique_ptr<Client> CreateClient(CommMode comm_mode);
};

}  // namespace ezcom