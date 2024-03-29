// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ezcom.proto

#include "ezcom.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace ezcom {
PROTOBUF_CONSTEXPR ProtobufMessage::ProtobufMessage(
    ::_pbi::ConstantInitialized)
  : int32_type_()
  , _int32_type_cached_byte_size_(0)
  , int64_type_()
  , _int64_type_cached_byte_size_(0)
  , uint32_type_()
  , _uint32_type_cached_byte_size_(0)
  , uint64_type_()
  , _uint64_type_cached_byte_size_(0)
  , float_type_()
  , double_type_()
  , bool_type_()
  , string_type_()
  , bytes_type_()
  , msg_id_(uint64_t{0u}){}
struct ProtobufMessageDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ProtobufMessageDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ProtobufMessageDefaultTypeInternal() {}
  union {
    ProtobufMessage _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ProtobufMessageDefaultTypeInternal _ProtobufMessage_default_instance_;
}  // namespace ezcom
static ::_pb::Metadata file_level_metadata_ezcom_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_ezcom_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_ezcom_2eproto = nullptr;

const uint32_t TableStruct_ezcom_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, msg_id_),
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, int32_type_),
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, int64_type_),
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, uint32_type_),
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, uint64_type_),
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, float_type_),
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, double_type_),
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, bool_type_),
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, string_type_),
  PROTOBUF_FIELD_OFFSET(::ezcom::ProtobufMessage, bytes_type_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::ezcom::ProtobufMessage)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::ezcom::_ProtobufMessage_default_instance_._instance,
};

const char descriptor_table_protodef_ezcom_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013ezcom.proto\022\005ezcom\"\330\001\n\017ProtobufMessage"
  "\022\016\n\006msg_id\030\001 \001(\004\022\022\n\nint32_type\030\002 \003(\005\022\022\n\n"
  "int64_type\030\003 \003(\003\022\023\n\013uint32_type\030\004 \003(\r\022\023\n"
  "\013uint64_type\030\005 \003(\004\022\022\n\nfloat_type\030\006 \003(\002\022\023"
  "\n\013double_type\030\007 \003(\001\022\021\n\tbool_type\030\010 \003(\010\022\023"
  "\n\013string_type\030\t \003(\t\022\022\n\nbytes_type\030\n \003(\014b"
  "\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_ezcom_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_ezcom_2eproto = {
    false, false, 247, descriptor_table_protodef_ezcom_2eproto,
    "ezcom.proto",
    &descriptor_table_ezcom_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_ezcom_2eproto::offsets,
    file_level_metadata_ezcom_2eproto, file_level_enum_descriptors_ezcom_2eproto,
    file_level_service_descriptors_ezcom_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_ezcom_2eproto_getter() {
  return &descriptor_table_ezcom_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_ezcom_2eproto(&descriptor_table_ezcom_2eproto);
namespace ezcom {

// ===================================================================

class ProtobufMessage::_Internal {
 public:
};

ProtobufMessage::ProtobufMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  int32_type_(arena),
  int64_type_(arena),
  uint32_type_(arena),
  uint64_type_(arena),
  float_type_(arena),
  double_type_(arena),
  bool_type_(arena),
  string_type_(arena),
  bytes_type_(arena) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:ezcom.ProtobufMessage)
}
ProtobufMessage::ProtobufMessage(const ProtobufMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      int32_type_(from.int32_type_),
      int64_type_(from.int64_type_),
      uint32_type_(from.uint32_type_),
      uint64_type_(from.uint64_type_),
      float_type_(from.float_type_),
      double_type_(from.double_type_),
      bool_type_(from.bool_type_),
      string_type_(from.string_type_),
      bytes_type_(from.bytes_type_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  msg_id_ = from.msg_id_;
  // @@protoc_insertion_point(copy_constructor:ezcom.ProtobufMessage)
}

inline void ProtobufMessage::SharedCtor() {
msg_id_ = uint64_t{0u};
}

ProtobufMessage::~ProtobufMessage() {
  // @@protoc_insertion_point(destructor:ezcom.ProtobufMessage)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void ProtobufMessage::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void ProtobufMessage::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void ProtobufMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:ezcom.ProtobufMessage)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  int32_type_.Clear();
  int64_type_.Clear();
  uint32_type_.Clear();
  uint64_type_.Clear();
  float_type_.Clear();
  double_type_.Clear();
  bool_type_.Clear();
  string_type_.Clear();
  bytes_type_.Clear();
  msg_id_ = uint64_t{0u};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ProtobufMessage::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 msg_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          msg_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated int32 int32_type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_int32_type(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 16) {
          _internal_add_int32_type(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated int64 int64_type = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt64Parser(_internal_mutable_int64_type(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 24) {
          _internal_add_int64_type(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated uint32 uint32_type = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedUInt32Parser(_internal_mutable_uint32_type(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 32) {
          _internal_add_uint32_type(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated uint64 uint64_type = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedUInt64Parser(_internal_mutable_uint64_type(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 40) {
          _internal_add_uint64_type(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated float float_type = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 50)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedFloatParser(_internal_mutable_float_type(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 53) {
          _internal_add_float_type(::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr));
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // repeated double double_type = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 58)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedDoubleParser(_internal_mutable_double_type(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 57) {
          _internal_add_double_type(::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr));
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      // repeated bool bool_type = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 66)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedBoolParser(_internal_mutable_bool_type(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 64) {
          _internal_add_bool_type(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated string string_type = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 74)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_string_type();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "ezcom.ProtobufMessage.string_type"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<74>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated bytes bytes_type = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 82)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_bytes_type();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<82>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* ProtobufMessage::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ezcom.ProtobufMessage)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 msg_id = 1;
  if (this->_internal_msg_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_msg_id(), target);
  }

  // repeated int32 int32_type = 2;
  {
    int byte_size = _int32_type_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          2, _internal_int32_type(), byte_size, target);
    }
  }

  // repeated int64 int64_type = 3;
  {
    int byte_size = _int64_type_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt64Packed(
          3, _internal_int64_type(), byte_size, target);
    }
  }

  // repeated uint32 uint32_type = 4;
  {
    int byte_size = _uint32_type_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteUInt32Packed(
          4, _internal_uint32_type(), byte_size, target);
    }
  }

  // repeated uint64 uint64_type = 5;
  {
    int byte_size = _uint64_type_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteUInt64Packed(
          5, _internal_uint64_type(), byte_size, target);
    }
  }

  // repeated float float_type = 6;
  if (this->_internal_float_type_size() > 0) {
    target = stream->WriteFixedPacked(6, _internal_float_type(), target);
  }

  // repeated double double_type = 7;
  if (this->_internal_double_type_size() > 0) {
    target = stream->WriteFixedPacked(7, _internal_double_type(), target);
  }

  // repeated bool bool_type = 8;
  if (this->_internal_bool_type_size() > 0) {
    target = stream->WriteFixedPacked(8, _internal_bool_type(), target);
  }

  // repeated string string_type = 9;
  for (int i = 0, n = this->_internal_string_type_size(); i < n; i++) {
    const auto& s = this->_internal_string_type(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      s.data(), static_cast<int>(s.length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "ezcom.ProtobufMessage.string_type");
    target = stream->WriteString(9, s, target);
  }

  // repeated bytes bytes_type = 10;
  for (int i = 0, n = this->_internal_bytes_type_size(); i < n; i++) {
    const auto& s = this->_internal_bytes_type(i);
    target = stream->WriteBytes(10, s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ezcom.ProtobufMessage)
  return target;
}

size_t ProtobufMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ezcom.ProtobufMessage)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 int32_type = 2;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      Int32Size(this->int32_type_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _int32_type_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // repeated int64 int64_type = 3;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      Int64Size(this->int64_type_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _int64_type_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // repeated uint32 uint32_type = 4;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      UInt32Size(this->uint32_type_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _uint32_type_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // repeated uint64 uint64_type = 5;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      UInt64Size(this->uint64_type_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _uint64_type_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // repeated float float_type = 6;
  {
    unsigned int count = static_cast<unsigned int>(this->_internal_float_type_size());
    size_t data_size = 4UL * count;
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    total_size += data_size;
  }

  // repeated double double_type = 7;
  {
    unsigned int count = static_cast<unsigned int>(this->_internal_double_type_size());
    size_t data_size = 8UL * count;
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    total_size += data_size;
  }

  // repeated bool bool_type = 8;
  {
    unsigned int count = static_cast<unsigned int>(this->_internal_bool_type_size());
    size_t data_size = 1UL * count;
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    total_size += data_size;
  }

  // repeated string string_type = 9;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(string_type_.size());
  for (int i = 0, n = string_type_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      string_type_.Get(i));
  }

  // repeated bytes bytes_type = 10;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(bytes_type_.size());
  for (int i = 0, n = bytes_type_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
      bytes_type_.Get(i));
  }

  // uint64 msg_id = 1;
  if (this->_internal_msg_id() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_msg_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ProtobufMessage::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    ProtobufMessage::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ProtobufMessage::GetClassData() const { return &_class_data_; }

void ProtobufMessage::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<ProtobufMessage *>(to)->MergeFrom(
      static_cast<const ProtobufMessage &>(from));
}


void ProtobufMessage::MergeFrom(const ProtobufMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ezcom.ProtobufMessage)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  int32_type_.MergeFrom(from.int32_type_);
  int64_type_.MergeFrom(from.int64_type_);
  uint32_type_.MergeFrom(from.uint32_type_);
  uint64_type_.MergeFrom(from.uint64_type_);
  float_type_.MergeFrom(from.float_type_);
  double_type_.MergeFrom(from.double_type_);
  bool_type_.MergeFrom(from.bool_type_);
  string_type_.MergeFrom(from.string_type_);
  bytes_type_.MergeFrom(from.bytes_type_);
  if (from._internal_msg_id() != 0) {
    _internal_set_msg_id(from._internal_msg_id());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ProtobufMessage::CopyFrom(const ProtobufMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ezcom.ProtobufMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ProtobufMessage::IsInitialized() const {
  return true;
}

void ProtobufMessage::InternalSwap(ProtobufMessage* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  int32_type_.InternalSwap(&other->int32_type_);
  int64_type_.InternalSwap(&other->int64_type_);
  uint32_type_.InternalSwap(&other->uint32_type_);
  uint64_type_.InternalSwap(&other->uint64_type_);
  float_type_.InternalSwap(&other->float_type_);
  double_type_.InternalSwap(&other->double_type_);
  bool_type_.InternalSwap(&other->bool_type_);
  string_type_.InternalSwap(&other->string_type_);
  bytes_type_.InternalSwap(&other->bytes_type_);
  swap(msg_id_, other->msg_id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ProtobufMessage::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_ezcom_2eproto_getter, &descriptor_table_ezcom_2eproto_once,
      file_level_metadata_ezcom_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace ezcom
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ezcom::ProtobufMessage*
Arena::CreateMaybeMessage< ::ezcom::ProtobufMessage >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ezcom::ProtobufMessage >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
