#pragma once

namespace ezcom {

enum class CommMode {
  kReqRep = 0,
  kPubSub = 1,
};

enum class TransportType {
  kInproc = 0,
  kIPC = 1,
  kTCP = 2,
};

}  // namespace ezcom