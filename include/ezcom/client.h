#pragma once
#include <functional>
#include <string>

#include "node.h"

namespace ezcom {

using ConnectionCallback = std::function<void(const ConnectionEvent&)>;

class Client : public Node {
 public:
  Client() = default;
  virtual ~Client() = default;
  virtual void Connect(const std::string& addr,
                       ConnectionCallback cb = nullptr) = 0;
};

}  // namespace ezcom