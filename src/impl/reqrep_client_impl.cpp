#include "reqrep_client_impl.h"

#include "ezcom/exception.h"
#include "utils/zmq_utils.h"
#include "zmq.h"

namespace ezcom {
namespace impl {

ReqRepClientImpl::ReqRepClientImpl(void* context,
                                   const TransportType& transport_type) {
  node_type_ = NodeType::kClient;
  comm_mode_ = CommMode::kReqRep;
  transport_type_ = transport_type;
  // Create zmq socket
  if (context == nullptr) {
    throw InvalidParamException("Zmq context is nullptr");
  }
  context_ = context;
  socket_ = zmq_socket(context_, ZMQ_REQ);
  // Create zmq monitor
  monitor_socket_ = utils::ZmqUtils::CreateMonitorSockets(context_, socket_,
                                                          "req-rep-client");
}

ReqRepClientImpl::ReqRepClientImpl(const TransportType& transport_type)
    : ReqRepClientImpl(zmq_ctx_new(), transport_type) {}

ReqRepClientImpl::~ReqRepClientImpl() {
  monitor_running_ = false;
  monitor_future_.get();

  // destory zmq resources
  zmq_close(socket_);
  zmq_close(monitor_socket_);
  if (transport_type_ != TransportType::kZmqInproc) {
    zmq_ctx_term(context_);
  }
}

void ReqRepClientImpl::Connect(const std::string& addr,
                               const ConnectionCallback& conn_cb) {
  int rc = -1;
  switch (transport_type_) {
    case TransportType::kZmqInproc: {
      rc = zmq_connect(socket_, ("inproc://" + addr).c_str());
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
    throw ResourceException("Zmq connect failed");
  }
  if (conn_cb) {
    monitor_running_ = true;
    monitor_future_ = std::async(std::launch::async, [this, conn_cb]() {
      while (monitor_running_) {
        int event = utils::ZmqUtils::GetMonitorEvent(monitor_socket_);
        // 第一次connect后退出
        if (event == ZMQ_EVENT_CONNECTED) {
          conn_cb(ConnectionEvent::kConnected);
          break;
        }
      }
    });
  }
}

}  // namespace impl
}  // namespace ezcom
