#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include "ezcom/node_factory.h"

using namespace ezcom;

void server_func(TransportType transport_type, std::string addr) {
  auto server_up = NodeFactory::CreateServer(transport_type);
  server_up->Bind(addr,
                  [](const std::shared_ptr<Message> &msg)
                      -> const std::shared_ptr<Message> {
                    auto reply_msg = std::make_shared<Message>();
                    reply_msg->AddInt32(msg->GetInt32(0) + 1);
                    return reply_msg;
                  });

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

void sync_client_func(TransportType transport_type, std::string addr) {
  auto client_up = NodeFactory::CreateClient(transport_type);
  std::promise<bool> promise;
  auto future = promise.get_future();

  client_up->Connect(addr, [&promise](const ConnectionEvent &event) {
    if (event == ConnectionEvent::kConnected) {
      promise.set_value(true);
    }
  });

  if (future.get()) {
    std::cout << "sync client connect success" << std::endl;

    auto msg = std::make_shared<Message>();
    msg->AddInt32(99);
    auto start = std::chrono::steady_clock::now();
    auto result = client_up->SyncRequest(msg, 1000);
    auto end = std::chrono::steady_clock::now();
    std::cout << "sync request time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
                     .count()
              << " us" << std::endl;

    std::cout << "sync result enum: " << (int)result.res_type << std::endl;
    if (result.res_type == ResultType::kSuccess) {
      std::cout << "sync result reply: " << result.rep_message->GetInt32(0)
                << std::endl;
    }
  }

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    std::cout << "usage: " << argv[0] << " [zmq_tcp|zmq_ipc]" << std::endl;
    return 0;
  }

  if (std::string(argv[1]) == "zmq_tcp") {
    std::thread t1(
        std::bind(server_func, TransportType::kZmqTcp, "127.0.0.1:7788"));
    std::thread t2(
        std::bind(sync_client_func, TransportType::kZmqTcp, "127.0.0.1:7788"));
    t1.join();
    t2.join();
  } else if (std::string(argv[1]) == "zmq_ipc") {
    std::thread t1(
        std::bind(server_func, TransportType::kZmqIpc, "01_test.ipc"));
    std::thread t2(
        std::bind(sync_client_func, TransportType::kZmqIpc, "01_test.ipc"));
    t1.join();
    t2.join();
  } else {
    std::cout << "usage: " << argv[0] << " [zmq_tcp|zmq_ipc]" << std::endl;
    return 0;
  }
  return 0;
}
