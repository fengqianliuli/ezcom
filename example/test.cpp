#include <chrono>
#include <iostream>
#include <thread>

#include "ezcom/node_factory.h"

int main(int argc, char const *argv[]) {
  auto client_up =
      ezcom::NodeFactory::CreateClient(ezcom::TransportType::kZmqTcp);
  client_up->Connect("127.0.0.1:8899", [](const ezcom::ConnectionEvent &event) {
    std::cout << "Connect event: " << (int)event << std::endl;
  });

  std::cout << "Press any key to exit..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  return 0;
}
