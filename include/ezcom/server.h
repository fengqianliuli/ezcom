#pragma once

#include <functional>
#include <string>

#include "message.h"
#include "node.h"

namespace ezcom {

using MessageHandler = std::function<const std::shared_ptr<Message>&(
    const std::shared_ptr<Message>&)>;

class Server : public Node {
 public:
  Server() = default;
  virtual ~Server() = default;
  virtual void Bind(const std::string& addr, const MessageHandler& handler) = 0;
};

}  // namespace ezcom
