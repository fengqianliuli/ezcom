#include "reqrep_client_impl.h"

#include "zmq.h"

namespace ezcom {

ReqRepClientImpl::ReqRepClientImpl(const void* context,
                                   const TransportType& transport_type) {
  node_type_ = NodeType::kClient;
  comm_mode_ = CommMode::kReqRep;
  transport_type_ = transport_type;
  if (context == nullptr) {
    throw std::runtime_error("zmq context is nullptr");
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
        throw std::runtime_error("Invalid ip address");
      }
      rc = zmq_connect(socket_, ("tcp://" + addr).c_str());
    } break;
    default:
      throw std::runtime_error("Invalid transport type");
  }
  if (rc != 0) {
    throw std::runtime_error("zmq connect failed");
  }
}

}  // namespace ezcom