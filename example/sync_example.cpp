#include <chrono>
#include <iostream>
#include <thread>

#include "message.h"
#include "requestor.h"
#include "responder.h"

#pragma pack(1)
struct Test_t {
  int int_value;
  double double_value;
  char char_value[10];
  std::string str_value;
};

#pragma pack ()

void send() {
  ezcom::Requestor req(ezcom::TransportType::kTcp, "127.0.0.1:7788");

  ezcom::Message msg;
  Test_t test_t{99, 99.99, "aaaaaaaa", "bbbbbbbbbb"};
  std::cout << "test_t size = " << sizeof(test_t) << std::endl;
  msg.AddBytes(&test_t, sizeof(test_t));

  auto start = std::chrono::system_clock::now();
  ezcom::Message rep = req.SyncRequest(msg, 3000);
  auto end = std::chrono::system_clock::now();
  std::cout << "REQ ====== END" << std::endl;
  std::cout << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(100));
}

void recv() {
  ezcom::Responder res(ezcom::TransportType::kTcp, "127.0.0.1:7788");

  res.StartServer([](const ezcom::Message& msg) {
    std::string test_t_str = msg.GetBytes(0);
    Test_t* test_t = reinterpret_cast<Test_t*>(const_cast<char *>(test_t_str.data()));

    std::cout << "recv msg: " << test_t->int_value << std::endl;
    std::cout << "recv msg: " << test_t->double_value << std::endl;
    std::cout << "recv msg: " << test_t->char_value << std::endl;
    std::cout << "recv msg: " << test_t->str_value << std::endl;

    ezcom::Message rep;
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
