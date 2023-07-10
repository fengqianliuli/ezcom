#pragma once

#include <functional>
#include <string>

#include "message.h"
#include "node.h"

namespace ezcom {

using MsgCallback = std::function<void(const std::shared_ptr<Message>&)>;

class Subscriber : public Node {
 public:
  Subscriber() = default;
  virtual ~Subscriber() = default;
  virtual void Subscribe(const std::string& addr, const MsgCallback& msg_cb,
                         const std::string& topic = "") = 0;
};

}  // namespace ezcom
