#include "responder.h"

#include <chrono>
#include <thread>

#include "pub_sub/async_responder_impl.h"

namespace ezcom {

Responder::Responder(TransportType transport_type, std::string addr) {
  switch (transport_type) {
    case TransportType::kTcp:
      if (addr.find(':') == std::string::npos) {
        throw std::invalid_argument("tcp address must be in format of ip:port");
      }
      addr = "tcp://" + addr;
      break;
    case TransportType::kIpc:
      if (addr.find(':') == std::string::npos) {
        addr = "ipc:///tmp/" + addr + ":0";
      } else {
        addr = "ipc:///tmp/" + addr;
      }
      break;
    default:
      break;
  }
  async_responder_ = std::make_shared<AsyncResponderImpl>(addr);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

Responder::Responder(TransportType transport_type, std::string local_addr,
                     std::string remote_addr) {
  switch (transport_type) {
    case TransportType::kTcp:
      if (local_addr.find(':') == std::string::npos ||
          remote_addr.find(':') == std::string::npos) {
        throw std::invalid_argument("tcp address must be in format of ip:port");
      }
      local_addr = "tcp://" + local_addr;
      remote_addr = "tcp://" + remote_addr;
      break;
    case TransportType::kIpc:
      local_addr = "ipc:///tmp/" + local_addr;
      remote_addr = "ipc:///tmp/" + remote_addr;
      break;
    default:
      break;
  }
  async_responder_ =
      std::make_shared<AsyncResponderImpl>(local_addr, remote_addr);
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
