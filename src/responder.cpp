#include "responder.h"

#include <chrono>
#include <thread>

#include "req_rep/async_responder_impl.h"

namespace ezcom {

Responder::Responder(TransportType transport_type,
                     const std::string& server_addr) {
  std::string tmp_addr;
  switch (transport_type) {
    case TransportType::kTcp:
      if (server_addr.find(':') == std::string::npos) {
        throw std::invalid_argument("tcp address must be in format of ip:port");
      }
      tmp_addr = "tcp://" + server_addr;
      break;
    case TransportType::kIpc:
      if (server_addr.find(':') == std::string::npos) {
        tmp_addr = "ipc:///tmp/" + server_addr + ":0";
      } else {
        tmp_addr = "ipc:///tmp/" + server_addr;
      }
      break;
    default:
      break;
  }
  async_responder_ = std::make_shared<AsyncResponderImpl>(tmp_addr);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

Responder::~Responder() { async_responder_ = nullptr; }

void Responder::StartServer(MsgCallback msg_callback) {
  async_responder_->StartServer(msg_callback);
}

void Responder::StartServerForgot(MsgCallbackForgot msg_callback) {
  async_responder_->StartServer([msg_callback](const Message& msg) -> Message {
    msg_callback(msg);
    return Message();
  });
}

void Responder::StopServer() { async_responder_->StopServer(); }

}  // namespace ezcom
