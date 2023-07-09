#include "ezcom/node_factory.h"

#include "ezcom/exception.h"
#include "impl/reqrep_client_impl.h"
#include "impl/reqrep_server_impl.h"

namespace ezcom {

std::unique_ptr<Client> NodeFactory::CreateClient(
    const TransportType& transport_type) {
  // 返回重定义转换为Client的Node
  return std::unique_ptr<Client>(reinterpret_cast<Client*>(
      CreateNode(NodeType::kClient, CommMode::kReqRep, transport_type)
          .release()));
}

std::unique_ptr<Server> NodeFactory::CreateServer(
    const TransportType& transport_type) {
  return std::unique_ptr<Server>(reinterpret_cast<Server*>(
      CreateNode(NodeType::kServer, CommMode::kReqRep, transport_type)
          .release()));
}

void NodeFactory::CreateZmqInprocNodes(
    int node_num, std::unique_ptr<Server>* server,
    std::vector<std::unique_ptr<Client>*>& clients) {
  std::vector<std::unique_ptr<Node>> nodes =
      CreateZmqInprocNode(CommMode::kReqRep, node_num);
  *server =
      std::unique_ptr<Server>(reinterpret_cast<Server*>(nodes[0].release()));
  for (int i = 1; i < node_num; ++i) {
    clients.push_back(new std::unique_ptr<Client>(
        reinterpret_cast<Client*>(nodes[i].release())));
  }
}

std::unique_ptr<Node> NodeFactory::CreateNode(
    const NodeType& node_type, const CommMode& comm_mode,
    const TransportType& transport_type) {
  if (transport_type == TransportType::kZmqInproc) {
    throw InvalidParamException("Not support transport type[kZmqInproc]");
  }
  switch (comm_mode) {
    case CommMode::kReqRep: {
      if (node_type == NodeType::kClient) {
        return std::make_unique<impl::ReqRepClientImpl>(transport_type);
      } else if (node_type == NodeType::kServer) {
        return std::make_unique<impl::ReqRepServerImpl>(transport_type);
      }
    } break;
    case CommMode::kPubSub:
      throw InvalidParamException("Not support communication mode[kPubSub]");
    default:
      throw InvalidParamException("Unknown communication mode");
  }
  return nullptr;
}

std::vector<std::unique_ptr<Node>> NodeFactory::CreateZmqInprocNode(
    const CommMode& comm_mode, int node_num) {
  // TODO: 实现
  return std::vector<std::unique_ptr<Node>>();
}

}  // namespace ezcom