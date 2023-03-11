#include <chrono>
#include <iostream>
#include <thread>

#include "requestor.h"
#include "responder.h"
#include "message.h"

constexpr int kDataSize = 1024 * 1024 * 20;

void send() {
  ezcom::Requestor req("tcp://127.0.0.1:7788");
  // 在rep启动之前发送消息，消息将会丢失，但rep不会崩溃
  uint8_t* bytes = new uint8_t[kDataSize];

  for (int i = 0; i < 10; ++i) {
    ezcom::Message msg;
    // msg.AddInt32(i);
    // msg.AddString("this is test request msg");
    msg.AddBytes(bytes, kDataSize);
    auto start = std::chrono::system_clock::now();
    int size = req.RequestForgot(msg);
    auto end = std::chrono::system_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;
    std::cout << "REQ ====== END, msg len: " << size << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  delete [] bytes;


  std::this_thread::sleep_for(std::chrono::seconds(100));
}

void recv() {
  // 故意晚启动rep，让req先发送消息，req之前发送的消息将会丢失
  std::this_thread::sleep_for(std::chrono::seconds(3));

  ezcom::Responder res("tcp://127.0.0.1:7788");
  res.StartServerForgot([](const ezcom::Message& msg) {
    std::cout << "REP +++++++ recv msg size: " << msg.GetBytes(0).size() << std::endl;
    // std::cout << "REP +++++++ recv msg: " << msg.GetInt32(0) << std::endl;
    // std::cout << "REP +++++++ recv msg: " << msg.GetString(0) << std::endl;
  });

  std::this_thread::sleep_for(std::chrono::seconds(100));
}

int main(int argc, char const* argv[]) {
  std::thread t1(send);
  std::thread t2(recv);
  t1.join();
  t2.join();
  return 0;
}
