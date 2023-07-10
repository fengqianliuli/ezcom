#pragma once

namespace ezcom {

constexpr int kZmqRcvTimeout = 1000;
constexpr int kZmqSndTimeout = 1000;

enum class NodeType {
  kClient = 0,
  kServer = 1,
  kPublisher = 2,
  kSubscriber = 3,
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

enum class ResultType {
  kSuccess = 0,
  kTimeout = 1,
  kCommError = 2,
  kInvaildParam = 3,
  kUnknownError = 4,
};

}  // namespace ezcom