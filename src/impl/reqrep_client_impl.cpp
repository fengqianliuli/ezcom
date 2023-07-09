#include "reqrep_client_impl.h"

#include "ezcom/exception.h"
#include "zmq.h"

namespace ezcom {

ReqRepClientImpl::ReqRepClientImpl(const void* context,
                                   const TransportType& transport_type) {
  node_type_ = NodeType::kClient;
  comm_mode_ = CommMode::kReqRep;
  transport_type_ = transport_type;
  if (context == nullptr) {
    throw InvalidParamException("Zmq context is nullptr");
  }
  socket_ = zmq_socket(context_, ZMQ_REQ);
}

ReqRepClientImpl::ReqRepClientImpl(const TransportType& transport_type)
    : ReqRepClientImpl(zmq_ctx_new(), transport_type) {}

ReqRepClientImpl::~ReqRepClientImpl() {}

void ReqRepClientImpl::Connect(const std::string& addr, ConnectionCallback cb) {
  if (cb) {
    // TODO: zmq monitor
    // cb(ConnectionEvent::kConnecting);
  }
  int rc = -1;
  switch (transport_type_) {
    case TransportType::kZmqInproc: {
    } break;
    case TransportType::kZmqIpc: {
      rc = zmq_connect(socket_, ("ipc:///tmp/" + addr).c_str());
    } break;
    case TransportType::kZmqTcp: {
      // 判断addr是否是ip地址
      if (addr.find(':') == std::string::npos) {
        throw InvalidParamException("Invalid ip address: " + addr);
      }
      rc = zmq_connect(socket_, ("tcp://" + addr).c_str());
    } break;
    default:
      throw InvalidParamException("Unknown transport type");
  }
  if (rc != 0) {
    throw ResourceInitException("Zmq connect failed");
  }
}

}  // namespace ezcom