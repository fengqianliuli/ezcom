#pragma once

#include "ezcom/publisher.h"

namespace ezcom {
namespace impl {

class PublisherImpl : public Publisher {
 public:
  PublisherImpl(void* context, const TransportType& transport_type);
  PublisherImpl(const TransportType& transport_type);
  PublisherImpl(const PublisherImpl&) = delete;
  PublisherImpl& operator=(const PublisherImpl&) = delete;
  ~PublisherImpl();

  void Bind(const std::string& addr) override;
  void Publish(const std::shared_ptr<Message>& msg,
               const std::string& topic = "") override;

 private:
  void* context_;
  void* socket_;
};

}  // namespace impl
}  // namespace ezcom
