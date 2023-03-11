#include <chrono>
#include <iostream>
#include <thread>

#include "message.h"
#include "requestor.h"
#include "responder.h"

#pragma pack(1)
struct Test_t {
  int int_value;
  char char_value[10];
  std::string str_value;
};

#pragma pack ()

void send() {
  ezcom::Requestor req("tcp://127.0.0.1:7788");
  // std::this_thread::sleep_for(std::chrono::milliseconds(1));

  ezcom::Message msg;
  // msg.AddInt32(99);
  // msg.AddString("this is test request msg");
  Test_t test_t{99, "aaaaaaaa", "bbbbbbbbbb"};
  msg.AddBytes(&test_t, sizeof(test_t));

  auto start = std::chrono::system_clock::now();
  ezcom::Message rep = req.SyncRequest(msg, 3000);
  auto end = std::chrono::system_clock::now();
  std::cout << "REQ ====== END" << std::endl;
  std::cout << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(100));
}

void recv() {
  ezcom::Responder res("tcp://127.0.0.1:7788");

  res.StartServer([](const ezcom::Message& msg) {
    std::string test_t_str = msg.GetBytes(0);
    Test_t* test_t = reinterpret_cast<Test_t*>(const_cast<char *>(test_t_str.data()));

    std::cout << "recv msg: " << test_t->int_value << " " << test_t->char_value << " " << test_t->str_value << std::endl;


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
