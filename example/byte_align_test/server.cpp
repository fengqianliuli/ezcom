#include <chrono>
#include <iostream>
#include <thread>

#include "message.h"
#include "msg.h"
#include "responder.h"

int main(int argc, char const* argv[]) {
  if (argc < 3) {
    std::cout << "param must has local addr and remote addr !" << std::endl;
    return -1;
  }
  std::string local_addr = argv[1];
  std::string remote_addr = argv[2];
  ezcom::Responder res(ezcom::TransportType::kTcp, local_addr, remote_addr);

  res.StartServer([](const ezcom::Message& msg) {
    std::string test_t_str = msg.GetBytes(0);
    ezcom::TestMsg_t* test_t = reinterpret_cast<ezcom::TestMsg_t*>(
        const_cast<char*>(test_t_str.data()));

    std::cout << "recv msg: " << test_t->int_value << std::endl;
    std::cout << "recv msg: " << test_t->double_value << std::endl;
    std::cout << "recv msg: " << test_t->char_value << std::endl;

    ezcom::Message rep;
    return rep;
  });

  std::this_thread::sleep_for(std::chrono::seconds(100));
  return 0;
}
