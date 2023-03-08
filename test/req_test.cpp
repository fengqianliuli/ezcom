#include <chrono>
#include <iostream>
#include <thread>

#include "message.h"
#include "src/req_rep/requestor_impl.h"
#include "src/req_rep/responder_impl.h"

void send() {
  ezcom::RequestorImpl req("tcp://127.0.0.1:7788");
  ezcom::Message msg;
  msg.AddInt32(99);
  msg.AddString("this is test request msg");
  ezcom::Message rep = req.SyncRequest(msg);

  std::cout << "REQ ====== reply msg: " << std::endl;
  std::cout << "REQ ====== reply msg: " << rep.GetInt32(0) << std::endl;
  std::cout << "REQ ====== reply msg: " << rep.GetString(0) << std::endl;
}

void recv() {
  ezcom::ResponderImpl res("tcp://127.0.0.1:7788");
  res.StartServer([](const ezcom::Message& msg) {
    std::cout << "REP +++++++ recv msg: " << std::endl;
    std::cout << "REP +++++++ recv msg: " << msg.GetInt32(0) << std::endl;
    std::cout << "REP +++++++ recv msg: " << msg.GetString(0) << std::endl;
    ezcom::Message rep;
    rep.AddInt32(100);
    rep.AddString("this is test response reply");
    return rep;
  });

  std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main(int argc, char const* argv[]) {
  std::thread t1(send);
  std::thread t2(recv);
  t1.join();
  t2.join();
  return 0;
}
