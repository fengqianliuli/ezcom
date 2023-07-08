#pragma once

namespace ezcom {

enum class CommMode {
  kReqRep = 0,
  kPubSub = 1,
};

enum class TransportType {
  kZmqInproc = 0,
  kZmqIpc = 1,
  kZmqTcp = 2,
};

}  // namespace ezcom