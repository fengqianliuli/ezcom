#pragma once

#include "ezcom/client.h"

namespace ezcom {

class PubsubClientImpl : public Client {
 public:
  PubsubClientImpl();
  ~PubsubClientImpl();
};

}  // namespace ezcom