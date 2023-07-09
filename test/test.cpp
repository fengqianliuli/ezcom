#include <chrono>
#include <iostream>
#include <thread>

#include "ezcom/node_factory.h"

using namespace ezcom;

void client_func() {
  auto client_up = NodeFactory::CreateClient(TransportType::kZmqTcp);
  client_up->Connect("127.0.0.1:8899", [](const ConnectionEvent &event) {
    std::cout << "Connect event: " << (int)event << std::endl;
  });

  std::cout << "CreateClient already return ..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
}

void server_func() {
  auto server_up = NodeFactory::CreateServer(TransportType::kZmqTcp);
  server_up->Bind("127.0.0.1:8899");

  std::cout << "CreateServer already return ..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(4));
}

int main(int argc, char const *argv[]) {
  std::thread client_thread(client_func);
  std::thread server_thread(server_func);
  client_thread.join();
  server_thread.join();
  return 0;
}
