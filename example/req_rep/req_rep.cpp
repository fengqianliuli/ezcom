#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include "ezcom/node_factory.h"

using namespace ezcom;

void server_func() {
  // create server node with zmq_tcp protocol, or you can choose
  // zmq_ipc protocol by use [TransportType::kZmqIpc]
  auto server_up = NodeFactory::CreateServer(TransportType::kZmqTcp);
  // bind server to address and setting message handle callback function
  // this callback function will be called when server receive message
  // and this callback function must return a message
  server_up->Bind("127.0.0.1:8899",
                  [](const std::shared_ptr<Message> &msg)
                      -> const std::shared_ptr<Message> {
                    auto reply_msg = std::make_shared<Message>();
                    reply_msg->AddInt32(msg->GetInt32(0) + 1);
                    return reply_msg;
                  });

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

void sync_client_func() {
  // create client node with zmq_tcp protocol
  auto client_up = NodeFactory::CreateClient(TransportType::kZmqTcp);
  std::promise<bool> promise;
  auto future = promise.get_future();

  // connect to server address and setting connection event callback function
  // this callback function will be called when client connect to server
  client_up->Connect("127.0.0.1:8899",
                     [&promise](const ConnectionEvent &event) {
                       if (event == ConnectionEvent::kConnected) {
                         promise.set_value(true);
                       }
                     });

  if (future.get()) {
    std::cout << "sync client connect success" << std::endl;

    // create message
    auto msg = std::make_shared<Message>();
    msg->AddInt32(99);
    // sync request message to server and wait for reply
    // you can set timeout(ms) for sync request, default value is -1
    // means wait forever
    auto result = client_up->SyncRequest(msg, 1000);
    // return value is a struct [Result]
    // it contains a enum [ResultType] and a shared_ptr [rep_message]
    // you can check [ResultType] to see if request success and why request
    // failed if success, you can get reply message from [rep_message] if
    // failed, [rep_message] will be nullptr
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

  if (future.get()) {
    std::cout << "async client connect success" << std::endl;

    auto msg = std::make_shared<Message>();
    msg->AddInt32(99);
    // async request message to server and setting callback function and
    // timeout(ms). timeout default value is -1 means wait forever
    // this callback function will be called when request success or
    // failed, result will be passed to callback function.
    // if success, [result.res_type] will be [ResultType::kSuccess] and
    // [result.rep_message] will be reply message.
    // if failed, [result.res_type] will be why request failed and
    // [result.rep_message] will be nullptr.
    client_up->AsyncRequest(
        msg,
        [](const Result result) {
          std::cout << "result enum: " << (int)result.res_type << std::endl;
          if (result.res_type == ResultType::kSuccess) {
            std::cout << "result reply: " << result.rep_message->GetInt32(0)
                      << std::endl;
          }
        },
        1000);
  }

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(int argc, char const *argv[]) {
  std::thread t1(sync_client_func);
  std::thread t2(async_client_func);
  std::thread t3(server_func);
  t1.join();
  t2.join();
  t3.join();
  return 0;
}
