#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include "ezcom/node_factory.h"

using namespace ezcom;

void client_func() {
  auto client_up = NodeFactory::CreateClient(TransportType::kZmqTcp);
  std::promise<bool> promise;
  auto future = promise.get_future();
  client_up->Connect("127.0.0.1:8899",
                     [&promise](const ConnectionEvent &event) {
                       if (event == ConnectionEvent::kConnected) {
                         promise.set_value(true);
                       }
                     });
  std::cout << "CreateClient already return ..." << std::endl;

  if (future.get()) {
    std::cout << "client connect success" << std::endl;
    auto msg = std::make_shared<Message>();
    msg->AddInt32(99);
    auto result = client_up->SyncRequest(msg);
    std::cout << "result enum: " << (int)result.res_type << std::endl;
    std::cout << "result reply: " << result.rep_message->GetInt32(0)
              << std::endl;
  }

  std::this_thread::sleep_for(std::chrono::seconds(3));
}

void server_func() {
  auto server_up = NodeFactory::CreateServer(TransportType::kZmqTcp);
  server_up->Bind("127.0.0.1:8899",
                  [](const std::shared_ptr<Message> &msg)
                      -> const std::shared_ptr<Message> {
                    auto reply_msg = std::make_shared<Message>();
                    reply_msg->AddInt32(msg->GetInt32(0) + 1);
                    return reply_msg;
                  });
  std::cout << "CreateServer already return ..." << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(int argc, char const *argv[]) {
  std::thread client_thread(client_func);
  std::thread server_thread(server_func);
  client_thread.join();
  server_thread.join();
  return 0;
}
