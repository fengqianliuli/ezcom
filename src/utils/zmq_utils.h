#pragma once

#include <stdlib.h>
#include <string.h>

#include "ezcom/exception.h"
#include "zmq.h"

namespace ezcom {
namespace utils {

class ZmqUtils {
 public:
  static int GetMonitorEvent(void *monitor, int *value = nullptr,
                             char **address = nullptr) {
    // First frame in message contains event number and value
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    if (zmq_msg_recv(&msg, monitor, 0) == -1)
      return -1;  // Interrupted, presumably
    // assert(zmq_msg_more(&msg));

    uint8_t *data = (uint8_t *)zmq_msg_data(&msg);
    uint16_t event = *(uint16_t *)(data);
    if (value) *value = *(uint32_t *)(data + 2);

    // Second frame in message contains event address
    zmq_msg_init(&msg);
    if (zmq_msg_recv(&msg, monitor, 0) == -1)
      return -1;  // Interrupted, presumably
    // assert(!zmq_msg_more(&msg));

    if (address) {
      uint8_t *data = (uint8_t *)zmq_msg_data(&msg);
      size_t size = zmq_msg_size(&msg);
      *address = (char *)malloc(size + 1);
      memcpy(*address, data, size);
      (*address)[size] = 0;
    }
    return event;
  }

  static void *CreateMonitorSockets(void *context, void *socket,
                                    const std::string &monitor_endpoint) {
    // Monitor all events on socket
    std::string endpoint = "inproc://" + monitor_endpoint;
    int rc = zmq_socket_monitor(socket, endpoint.c_str(), ZMQ_EVENT_ALL);
    if (rc != 0) {
      throw ResourceException("Failed to monitor socket");
    }
    // Create a socket for collecting monitor events
    void *monitor_socket = zmq_socket(context, ZMQ_PAIR);
    if (monitor_socket == nullptr) {
      throw ResourceException("Failed to create monitor socket");
    }
    // Connect to the inproc endpoint so it'll get events
    rc = zmq_connect(monitor_socket, endpoint.c_str());
    if (rc != 0) {
      throw ResourceException("Failed to connect monitor socket");
    }
    return monitor_socket;
  }
};

}  // namespace utils
}  // namespace ezcom