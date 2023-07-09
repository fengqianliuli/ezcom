#pragma once

#include <string>

#include "node.h"

namespace ezcom {

class Server : public Node {
 public:
  Server() = default;
  virtual ~Server() = default;
  virtual void Bind(const std::string& addr) = 0;
};

}  // namespace ezcom
