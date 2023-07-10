#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include "ezcom/node_factory.h"

using namespace ezcom;

void server_func() {
  auto server_up = NodeFactory::CreateServer(TransportType::kZmqTcp);
  server_up->Bind("127.0.0.1:8899",
                  [](const std::shared_ptr<Message> &msg)
                      -> const std::shared_ptr<Message> {
                    auto reply_msg = std::make_shared<Message>();
                    reply_msg->AddInt32(msg->GetInt32(0) + 1);

                    std::this_thread::sleep_for(std::chrono::seconds(5));
                    return reply_msg;
                  });
  std::cout << "CreateServer already return ..." << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

void sync_client_func() {
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
    auto result = client_up->SyncRequest(msg, 1000);

    std::cout << "result enum: " << (int)result.res_type << std::endl;
    if (result.res_type == ResultType::kSuccess) {
      std::cout << "result reply: " << result.rep_message->GetInt32(0)
                << std::endl;
    }
  }

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

void async_client_func() {
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
    client_up->AsyncRequest(msg, [](const Result result) {
      std::cout << "result enum: " << (int)result.res_type << std::endl;
      if (result.res_type == ResultType::kSuccess) {
        std::cout << "result reply: " << result.rep_message->GetInt32(0)
                  << std::endl;
      }
    }, 1000);
    std::cout << "AsyncRequest already return ..." << std::endl;
  }

  std::this_thread::sleep_for(std::chrono::seconds(10));

}

void pub_func() {
  auto pub = NodeFactory::CreatePublisher(TransportType::kZmqTcp);
  pub->Bind("127.0.0.1:7788");
  for (int i = 0; i  < 10; i++) {
    auto msg = std::make_shared<Message>();
    msg->AddInt32(99);
    pub->Publish(msg, "test_topic");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void sub_func() {
  auto sub = NodeFactory::CreateSubscriber(TransportType::kZmqTcp);
  sub->Subscribe("127.0.0.1:7788", [](const std::shared_ptr<Message> &msg) {
    std::cout << "recv msg: " << msg->GetInt32(0) << std::endl;
  }, "test_topic");

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(int argc, char const *argv[]) {
  // *****************client-server test********************
  // std::thread t1(sync_client_func);
  std::thread t2(async_client_func);
  std::thread t3(server_func);
  // t1.join();
  t2.join();
  t3.join();


  // *****************pub-sub test********************
  // std::thread t1(pub_func);
  // std::thread t2(sub_func);
  // t1.join();
  // t2.join();
  return 0;
}
