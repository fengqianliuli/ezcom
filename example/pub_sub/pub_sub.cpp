#include <chrono>
#include <iostream>
#include <thread>

#include "ezcom/node_factory.h"

using namespace ezcom;

void pub_func() {
  // create publisher node with zmq_tcp protocol, or you can choose
  // zmq_ipc protocol by use [TransportType::kZmqIpc]
  auto pub = NodeFactory::CreatePublisher(TransportType::kZmqTcp);
  // bind publisher to address
  pub->Bind("127.0.0.1:7788");
  for (int i = 0; i < 10; i++) {
    // create message
    auto msg = std::make_shared<Message>();
    msg->AddInt32(i);
    // publish message to specific topic
    pub->Publish(msg, "test_topic");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

void sub_func() {
  // subscriber start later than publisher, will miss some message
  std::this_thread::sleep_for(std::chrono::seconds(1));
  // create subscriber node with zmq_tcp protocol
  auto sub = NodeFactory::CreateSubscriber(TransportType::kZmqTcp);
  // subscribe to address and setting callback function and topic
  sub->Subscribe(
      "127.0.0.1:7788",
      [](const std::shared_ptr<Message> &msg) {
        std::cout << "recv msg: " << msg->GetInt32(0) << std::endl;
      },
      "test_topic");

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(int argc, char const *argv[]) {
  std::thread t1(pub_func);
  std::thread t2(sub_func);
  t1.join();
  t2.join();
  return 0;
}
