#include <chrono>
#include <iostream>
#include <thread>

#include "async_requestor.h"
#include "async_responder.h"
#include "message.h"

void send() {
  ezcom::AsyncRequestor req("tcp://127.0.0.1:7788");
  // req发送异步请求时，如果此时rep还没有启动，那么req的本次消息将会丢失
  // 所以这里加了一个sleep，让rep先启动完成
  std::this_thread::sleep_for(std::chrono::seconds(1));

  ezcom::Message msg;
  msg.AddInt32(99);
  msg.AddString("this is test request msg");
  int size = req.AsyncRequest(msg, [](const ezcom::Message& rep) {
    std::cout << "REQ ====== reply msg: " << rep.GetInt32(0) << std::endl;
    std::cout << "REQ ====== reply msg: " << rep.GetString(0) << std::endl;
  });
  std::cout << "REQ ====== END, msg len: " << size << std::endl;


  std::this_thread::sleep_for(std::chrono::seconds(100));
}

void recv() {
  ezcom::AsyncResponder res("tcp://127.0.0.1:7788");
  res.StartServer([](const ezcom::Message& msg) {
    std::cout << "REP +++++++ recv msg: " << msg.GetInt32(0) << std::endl;
    std::cout << "REP +++++++ recv msg: " << msg.GetString(0) << std::endl;
    ezcom::Message rep;
    rep.AddInt32(100);
    rep.AddString("this is test response reply");

    // 模拟耗时操作
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return rep;
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
