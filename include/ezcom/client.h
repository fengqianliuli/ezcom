#pragma once

namespace ezcom {

class Client {
 public:
  Client();
  virtual ~Client();

  virtual void Connect() = 0;
};

}  // namespace ezcom