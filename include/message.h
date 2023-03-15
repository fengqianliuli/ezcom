#pragma once

#include <memory>
#include <string>

namespace ezcom {

class ProtobufMessage;

class Message final {
  friend class RequestorImpl;
  friend class ResponderImpl;
  friend class AsyncRequestorImpl;
  friend class AsyncResponderImpl;

 public:
  Message();
  ~Message() = default;
  Message(const Message&) = default;
  Message& operator=(const Message&) = default;
  Message(Message&&) = default;
  Message& operator=(Message&&) = default;

  void AddDouble(const double& value);
  void AddFloat(const float& value);
  void AddInt32(const int32_t& value);
  void AddInt64(const int64_t& value);
  void AddUint32(const uint32_t& value);
  void AddUint64(const uint64_t& value);
  void AddBool(const bool& value);
  void AddString(const std::string& value);
  void AddBytes(const void* value, size_t size);

  void CleanDouble();
  void CleanFloat();
  void CleanInt32();
  void CleanInt64();
  void CleanUint32();
  void CleanUint64();
  void CleanBool();
  void CleanString();
  void CleanBytes();
  void CleanAll();

  int GetDoubleSize() const;
  int GetFloatSize() const;
  int GetInt32Size() const;
  int GetInt64Size() const;
  int GetUint32Size() const;
  int GetUint64Size() const;
  int GetBoolSize() const;
  int GetStringSize() const;
  int GetBytesSize() const;

  double GetDouble(int index) const;
  float GetFloat(int index) const;
  int32_t GetInt32(int index) const;
  int64_t GetInt64(int index) const;
  uint32_t GetUint32(int index) const;
  uint64_t GetUint64(int index) const;
  bool GetBool(int index) const;
  std::string GetString(int index) const;
  std::string GetBytes(int index) const;

  int64_t GetMsgId() const;
  void SetMsgId(const int64_t& msg_id);

 private:
  std::shared_ptr<ProtobufMessage> proto_msg_;
};

}  // namespace ezcom
