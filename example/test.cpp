#include "include/ezcom/client_factory.h"

int main(int argc, char const *argv[]) {
  auto client = ezcom::ClientFactory::CreateClient(ezcom::CommMode::kReqRep);
  client->Connect(addr, [](ezcom::Result res){
    std::cout << "Connected" << std::endl;
  }, timeout);


  ezcom::Message msg;
  msg.add("Hello");

  ezcom::Message resp = client->SyncRequest(msg, timeout);

  client->AsyncRequest(msg, [](ezcom::Message resp){}, timeout);
  return 0;
}
