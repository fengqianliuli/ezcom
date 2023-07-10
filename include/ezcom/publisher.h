#pragma once

#include <string>

#include "message.h"
#include "node.h"

namespace ezcom {

class Publisher : public Node {
 public:
  Publisher() = default;
  virtual ~Publisher() = default;
  virtual void Bind(const std::string& addr) = 0;
  virtual void Publish(const std::shared_ptr<Message>& msg,
                       const std::string& topic = "") = 0;
};

}  // namespace ezcom
