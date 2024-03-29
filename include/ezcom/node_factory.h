#pragma once

#include <memory>
#include <vector>

#include "client.h"
#include "publisher.h"
#include "server.h"
#include "subscriber.h"

namespace ezcom {

class NodeFactory {
 public:
  static std::unique_ptr<Client> CreateClient(
      const TransportType& transport_type);
  static std::unique_ptr<Server> CreateServer(
      const TransportType& transport_type);
  // TODO: inproc
  //   static void CreateZmqInprocNodes(int node_num, std::unique_ptr<Server>*
  //   server,
  //       std::vector<std::unique_ptr<Client>*>& clients);

  static std::unique_ptr<Publisher> CreatePublisher(
      const TransportType& transport_type);
  static std::unique_ptr<Subscriber> CreateSubscriber(
      const TransportType& transport_type);
  // TODO: inproc
  //   static void CreateZmqInprocNodes(int node_num, std::unique_ptr<Pub>* pub,
  //       std::vector<std::unique_ptr<Sub>*>& subs);
 private:
  static std::unique_ptr<Node> CreateNode(const NodeType& node_type,
                                          const CommMode& comm_mode,
                                          const TransportType& transport_type);
  static std::vector<std::unique_ptr<Node>> CreateZmqInprocNode(
      const CommMode& comm_mode, int node_num);
};

}  // namespace ezcom