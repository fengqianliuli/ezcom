#include <chrono>
#include <iostream>
#include <thread>

#include "message.h"
#include "requestor.h"
#include "responder.h"

void send() {
  ezcom::Requestor req("tcp://127.0.0.1:7788");
  // std::this_thread::sleep_for(std::chrono::milliseconds(1));

  ezcom::Message msg;
  msg.AddInt32(99);
  msg.AddString("this is test request msg");

  auto start = std::chrono::system_clock::now();
  ezcom::Message rep = req.SyncRequest(msg, 3000);
  auto end = std::chrono::system_clock::now();
  std::cout << "REQ ====== END" << std::endl;
  std::cout << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;
  std::cout << "REQ ====== reply msg: " << rep.GetInt32(0) << std::endl;
  std::cout << "REQ ====== reply msg: " << rep.GetString(0) << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(100));
}

void recv() {
  ezcom::Responder res("tcp://127.0.0.1:7788");

  res.StartServer([](const ezcom::Message& msg) {
    std::cout << "REP +++++++ recv msg: " << msg.GetInt32(0) << std::endl;
    std::cout << "REP +++++++ recv msg: " << msg.GetString(0) << std::endl;
    ezcom::Message rep;
    rep.AddInt32(100);
    rep.AddString("this is test response reply");

    // std::this_thread::sleep_for(std::chrono::seconds(1));
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
