#pragma once

#include "node.h"

namespace ezcom {

class Server : public Node {
 public:
  Server() = default;
  virtual ~Server() = default;
};

}  // namespace ezcom
