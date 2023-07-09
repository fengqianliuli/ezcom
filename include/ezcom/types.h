#pragma once

namespace ezcom {

enum class NodeType {
  kClient = 0,
  kServer = 1,
  kPub = 2,
  kSub = 3,
};

enum class CommMode {
  kReqRep = 0,
  kPubSub = 1,
};

enum class TransportType {
  kZmqInproc = 0,
  kZmqIpc = 1,
  kZmqTcp = 2,
};

enum class ConnectionEvent {
  kConnected = 0,
  kDisconnected = 1,
};

}  // namespace ezcom