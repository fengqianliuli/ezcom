#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include "ezcom/node_factory.h"

using namespace ezcom;

void sync_client_func(std::string addr) {
  auto client_up = NodeFactory::CreateClient(TransportType::kZmqTcp);

  client_up->Connect(addr, [](const ConnectionEvent &event) {
    std::cout << "event: " << (int)event << std::endl;
  });

  // if (future.get()) {
  //   std::cout << "sync client connect success" << std::endl;

  //   auto msg = std::make_shared<Message>();
  //   msg->AddInt32(99);

  //   auto result = client_up->SyncRequest(msg, 1000);

  //   std::cout << "sync result enum: " << (int)result.res_type << std::endl;
  //   if (result.res_type == ResultType::kSuccess) {
  //     std::cout << "sync result reply: " << result.rep_message->GetInt32(0)
  //               << std::endl;
  //   }
  // }

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "usage: " << argv[0] << " <addr>" << std::endl;
    return 0;
  }
  std::thread t1(sync_client_func, argv[1]);
  t1.join();
  return 0;
}
