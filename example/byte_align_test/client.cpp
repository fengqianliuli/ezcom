#include <chrono>
#include <iostream>
#include <thread>

#include "msg.h"
#include "message.h"
#include "requestor.h"

int main(int argc, char const* argv[]) {
  if (argc < 2) {
    std::cout << "param must has server addr !" << std::endl;
    return -1;
  }
  std::string server_addr = argv[1];
  ezcom::Requestor req(ezcom::TransportType::kTcp, server_addr);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  ezcom::Message msg;
  ezcom::TestMsg_t test_t{99, 99.99, "aaaaaaaa"};
  std::cout << "test_t size = " << sizeof(test_t) << std::endl;
  msg.AddBytes(&test_t, sizeof(test_t));

  for (int i = 0; i < 3; i++) {
    auto start = std::chrono::system_clock::now();
    ezcom::Message rep = req.SyncRequest(msg, 3000);
    auto end = std::chrono::system_clock::now();
    std::cout << "REQ ====== END" << std::endl;
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }


  std::this_thread::sleep_for(std::chrono::seconds(100));
  return 0;
}
