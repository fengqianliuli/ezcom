#include "reqrep_server_impl.h"

#include "ezcom/exception.h"
#include "zmq.h"

namespace ezcom {
namespace impl {

ReqRepServerImpl::ReqRepServerImpl(void* context,
                                   const TransportType& transport_type) {
  node_type_ = NodeType::kServer;
  comm_mode_ = CommMode::kReqRep;
  transport_type_ = transport_type;
  // Create zmq socket
  if (context == nullptr) {
    throw InvalidParamException("Zmq context is nullptr");
  }
  context_ = context;
  socket_ = zmq_socket(context_, ZMQ_REQ);
}

ReqRepServerImpl::ReqRepServerImpl(const TransportType& transport_type)
    : ReqRepServerImpl(zmq_ctx_new(), transport_type) {}

ReqRepServerImpl::~ReqRepServerImpl() {
  // destory zmq resources
  zmq_close(socket_);
  if (transport_type_ != TransportType::kZmqInproc) {
    zmq_ctx_term(context_);
  }
}

void ReqRepServerImpl::Bind(const std::string& addr) {
  int rc = -1;
  switch (transport_type_) {
    case TransportType::kZmqInproc: {
      rc = zmq_bind(socket_, ("inproc://" + addr).c_str());
    } break;
    case TransportType::kZmqIpc: {
      rc = zmq_bind(socket_, ("ipc:///tmp/" + addr).c_str());
    } break;
    case TransportType::kZmqTcp: {
      // 判断addr是否是ip地址
      if (addr.find(':') == std::string::npos) {
        throw InvalidParamException("Invalid ip address: " + addr);
      }
      rc = zmq_bind(socket_, ("tcp://" + addr).c_str());
    } break;
    default:
      throw InvalidParamException("Unknown transport type");
  }
  if (rc != 0) {
    throw ResourceException("Zmq bind failed");
  }
}

}  // namespace impl
}  // namespace ezcom
