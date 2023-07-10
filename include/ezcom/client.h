#pragma once
#include <functional>
#include <memory>
#include <string>

#include "message.h"
#include "node.h"

namespace ezcom {

struct Result {
  ResultType res_type;
  std::shared_ptr<Message> rep_message;
};

using ConnectionCallback = std::function<void(const ConnectionEvent&)>;
using ResultCallback = std::function<void(const Result)>;

class Client : public Node {
 public:
  Client() = default;
  virtual ~Client() = default;
  virtual void Connect(const std::string& addr,
                       const ConnectionCallback& conn_cb) = 0;
  virtual Result SyncRequest(const std::shared_ptr<Message>& req_message,
                             int timeout_ms = -1) = 0;
  virtual void AsyncRequest(const std::shared_ptr<Message>& req_message,
                            const ResultCallback& result_cb,
                            int timeout_ms = -1) = 0;
};

}  // namespace ezcom