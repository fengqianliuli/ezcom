#pragma once

#include "types.h"

namespace ezcom {

class Node {
 public:
  Node() = default;
  virtual ~Node() = default;

 protected:
  NodeType node_type_;
  CommMode comm_mode_;
  TransportType transport_type_;
};

}  // namespace ezcom

