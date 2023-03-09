#include "message.h"
#include "proto/gen/ezcom.pb.h"

namespace ezcom {

Message::Message() {
  proto_msg_ = std::make_shared<ProtobufMessage>();
}

void Message::SetMsgId(const int64_t& msg_id) {
  proto_msg_->set_msg_id(msg_id);
}

int64_t Message::GetMsgId() const {
  return proto_msg_->msg_id();
}

/********************ADD************************/

void Message::AddDouble(const double& value) {
  proto_msg_->add_double_type(value);
}

void Message::AddFloat(const float& value) {
  proto_msg_->add_float_type(value);
}

void Message::AddInt32(const int32_t& value) {
  proto_msg_->add_int32_type(value);
}

void Message::AddInt64(const int64_t& value) {
  proto_msg_->add_int64_type(value);
}

void Message::AddUint32(const uint32_t& value) {
  proto_msg_->add_uint32_type(value);
}

void Message::AddUint64(const uint64_t& value) {
  proto_msg_->add_uint64_type(value);
}

void Message::AddBool(const bool& value) {
  proto_msg_->add_bool_type(value);
}

void Message::AddString(const std::string& value) {
  proto_msg_->add_string_type(value);
}

void Message::AddBytes(const void* value, size_t size) {
  proto_msg_->add_bytes_type(value, size);
}

/********************CLEAN************************/

void Message::CleanDouble() {
  proto_msg_->clear_double_type();
}

void Message::CleanFloat() {
  proto_msg_->clear_float_type();
}

void Message::CleanInt32() {
  proto_msg_->clear_int32_type();
}

void Message::CleanInt64() {
  proto_msg_->clear_int64_type();
}

void Message::CleanUint32() {
  proto_msg_->clear_uint32_type();
}

void Message::CleanUint64() {
  proto_msg_->clear_uint64_type();
}

void Message::CleanBool() {
  proto_msg_->clear_bool_type();
}

void Message::CleanString() {
  proto_msg_->clear_string_type();
}

void Message::CleanBytes() {
  proto_msg_->clear_bytes_type();
}

void Message::CleanAll() {
  proto_msg_->clear_double_type();
  proto_msg_->clear_float_type();
  proto_msg_->clear_int32_type();
  proto_msg_->clear_int64_type();
  proto_msg_->clear_uint32_type();
  proto_msg_->clear_uint64_type();
  proto_msg_->clear_bool_type();
  proto_msg_->clear_string_type();
  proto_msg_->clear_bytes_type();
}

/********************GET SIZE************************/

int Message::GetDoubleSize() const {
  return proto_msg_->double_type_size();
}

int Message::GetFloatSize() const {
  return proto_msg_->float_type_size();
}

int Message::GetInt32Size() const {
  return proto_msg_->int32_type_size();
}

int Message::GetInt64Size() const {
  return proto_msg_->int64_type_size();
}

int Message::GetUint32Size() const {
  return proto_msg_->uint32_type_size();
}

int Message::GetUint64Size() const {
  return proto_msg_->uint64_type_size();
}

int Message::GetBoolSize() const {
  return proto_msg_->bool_type_size();
}

int Message::GetStringSize() const {
  return proto_msg_->string_type_size();
}

int Message::GetBytesSize() const {
  return proto_msg_->bytes_type_size();
}


/********************GET VALUE************************/

double Message::GetDouble(int index) const {
  return proto_msg_->double_type(index);
}

float Message::GetFloat(int index) const {
  return proto_msg_->float_type(index);
}

int32_t Message::GetInt32(int index) const {
  return proto_msg_->int32_type(index);
}

int64_t Message::GetInt64(int index) const {
  return proto_msg_->int64_type(index);
}

uint32_t Message::GetUint32(int index) const {
  return proto_msg_->uint32_type(index);
}

uint64_t Message::GetUint64(int index) const {
  return proto_msg_->uint64_type(index);
}

bool Message::GetBool(int index) const {
  return proto_msg_->bool_type(index);
}

std::string Message::GetString(int index) const {
  return proto_msg_->string_type(index);
}

std::string Message::GetBytes(int index) const {
  return proto_msg_->bytes_type(index);
}

}  // namespace ezcom
