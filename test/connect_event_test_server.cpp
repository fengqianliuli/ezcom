#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include "ezcom/node_factory.h"

using namespace ezcom;

void server_func(std::string addr) {
  auto server_up = NodeFactory::CreateServer(TransportType::kZmqTcp);
  server_up->Bind(addr,
                  [](const std::shared_ptr<Message> &msg)
                      -> const std::shared_ptr<Message> {
                    auto reply_msg = std::make_shared<Message>();
                    reply_msg->AddInt32(msg->GetInt32(0) + 1);
                    return reply_msg;
                  });

  std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "usage: " << argv[0] << " <addr>" << std::endl;
    return 0;
  }
  std::thread t1(server_func, argv[1]);
  t1.join();
  return 0;
}
