// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ezcom.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ezcom_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ezcom_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3020000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3020001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ezcom_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ezcom_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ezcom_2eproto;
namespace ezcom {
class ProtobufMessage;
struct ProtobufMessageDefaultTypeInternal;
extern ProtobufMessageDefaultTypeInternal _ProtobufMessage_default_instance_;
}  // namespace ezcom
PROTOBUF_NAMESPACE_OPEN
template<> ::ezcom::ProtobufMessage* Arena::CreateMaybeMessage<::ezcom::ProtobufMessage>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace ezcom {

// ===================================================================

class ProtobufMessage final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ezcom.ProtobufMessage) */ {
 public:
  inline ProtobufMessage() : ProtobufMessage(nullptr) {}
  ~ProtobufMessage() override;
  explicit PROTOBUF_CONSTEXPR ProtobufMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ProtobufMessage(const ProtobufMessage& from);
  ProtobufMessage(ProtobufMessage&& from) noexcept
    : ProtobufMessage() {
    *this = ::std::move(from);
  }

  inline ProtobufMessage& operator=(const ProtobufMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline ProtobufMessage& operator=(ProtobufMessage&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ProtobufMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const ProtobufMessage* internal_default_instance() {
    return reinterpret_cast<const ProtobufMessage*>(
               &_ProtobufMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ProtobufMessage& a, ProtobufMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(ProtobufMessage* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ProtobufMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ProtobufMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ProtobufMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ProtobufMessage& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const ProtobufMessage& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ProtobufMessage* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ezcom.ProtobufMessage";
  }
  protected:
  explicit ProtobufMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDoubleTypeFieldNumber = 1,
    kFloatTypeFieldNumber = 2,
    kInt32TypeFieldNumber = 3,
    kInt64TypeFieldNumber = 4,
    kUint32TypeFieldNumber = 5,
    kUint64TypeFieldNumber = 6,
    kBoolTypeFieldNumber = 7,
    kStringTypeFieldNumber = 8,
    kBytesTypeFieldNumber = 9,
  };
  // repeated double double_type = 1;
  int double_type_size() const;
  private:
  int _internal_double_type_size() const;
  public:
  void clear_double_type();
  private:
  double _internal_double_type(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >&
      _internal_double_type() const;
  void _internal_add_double_type(double value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >*
      _internal_mutable_double_type();
  public:
  double double_type(int index) const;
  void set_double_type(int index, double value);
  void add_double_type(double value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >&
      double_type() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >*
      mutable_double_type();

  // repeated float float_type = 2;
  int float_type_size() const;
  private:
  int _internal_float_type_size() const;
  public:
  void clear_float_type();
  private:
  float _internal_float_type(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< float >&
      _internal_float_type() const;
  void _internal_add_float_type(float value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< float >*
      _internal_mutable_float_type();
  public:
  float float_type(int index) const;
  void set_float_type(int index, float value);
  void add_float_type(float value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< float >&
      float_type() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< float >*
      mutable_float_type();

  // repeated int32 int32_type = 3;
  int int32_type_size() const;
  private:
  int _internal_int32_type_size() const;
  public:
  void clear_int32_type();
  private:
  int32_t _internal_int32_type(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      _internal_int32_type() const;
  void _internal_add_int32_type(int32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      _internal_mutable_int32_type();
  public:
  int32_t int32_type(int index) const;
  void set_int32_type(int index, int32_t value);
  void add_int32_type(int32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      int32_type() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      mutable_int32_type();

  // repeated int64 int64_type = 4;
  int int64_type_size() const;
  private:
  int _internal_int64_type_size() const;
  public:
  void clear_int64_type();
  private:
  int64_t _internal_int64_type(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int64_t >&
      _internal_int64_type() const;
  void _internal_add_int64_type(int64_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int64_t >*
      _internal_mutable_int64_type();
  public:
  int64_t int64_type(int index) const;
  void set_int64_type(int index, int64_t value);
  void add_int64_type(int64_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int64_t >&
      int64_type() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int64_t >*
      mutable_int64_type();

  // repeated uint32 uint32_type = 5;
  int uint32_type_size() const;
  private:
  int _internal_uint32_type_size() const;
  public:
  void clear_uint32_type();
  private:
  uint32_t _internal_uint32_type(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      _internal_uint32_type() const;
  void _internal_add_uint32_type(uint32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      _internal_mutable_uint32_type();
  public:
  uint32_t uint32_type(int index) const;
  void set_uint32_type(int index, uint32_t value);
  void add_uint32_type(uint32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      uint32_type() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      mutable_uint32_type();

  // repeated uint64 uint64_type = 6;
  int uint64_type_size() const;
  private:
  int _internal_uint64_type_size() const;
  public:
  void clear_uint64_type();
  private:
  uint64_t _internal_uint64_type(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint64_t >&
      _internal_uint64_type() const;
  void _internal_add_uint64_type(uint64_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint64_t >*
      _internal_mutable_uint64_type();
  public:
  uint64_t uint64_type(int index) const;
  void set_uint64_type(int index, uint64_t value);
  void add_uint64_type(uint64_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint64_t >&
      uint64_type() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint64_t >*
      mutable_uint64_type();

  // repeated bool bool_type = 7;
  int bool_type_size() const;
  private:
  int _internal_bool_type_size() const;
  public:
  void clear_bool_type();
  private:
  bool _internal_bool_type(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >&
      _internal_bool_type() const;
  void _internal_add_bool_type(bool value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >*
      _internal_mutable_bool_type();
  public:
  bool bool_type(int index) const;
  void set_bool_type(int index, bool value);
  void add_bool_type(bool value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >&
      bool_type() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >*
      mutable_bool_type();

  // repeated string string_type = 8;
  int string_type_size() const;
  private:
  int _internal_string_type_size() const;
  public:
  void clear_string_type();
  const std::string& string_type(int index) const;
  std::string* mutable_string_type(int index);
  void set_string_type(int index, const std::string& value);
  void set_string_type(int index, std::string&& value);
  void set_string_type(int index, const char* value);
  void set_string_type(int index, const char* value, size_t size);
  std::string* add_string_type();
  void add_string_type(const std::string& value);
  void add_string_type(std::string&& value);
  void add_string_type(const char* value);
  void add_string_type(const char* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& string_type() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_string_type();
  private:
  const std::string& _internal_string_type(int index) const;
  std::string* _internal_add_string_type();
  public:

  // repeated bytes bytes_type = 9;
  int bytes_type_size() const;
  private:
  int _internal_bytes_type_size() const;
  public:
  void clear_bytes_type();
  const std::string& bytes_type(int index) const;
  std::string* mutable_bytes_type(int index);
  void set_bytes_type(int index, const std::string& value);
  void set_bytes_type(int index, std::string&& value);
  void set_bytes_type(int index, const char* value);
  void set_bytes_type(int index, const void* value, size_t size);
  std::string* add_bytes_type();
  void add_bytes_type(const std::string& value);
  void add_bytes_type(std::string&& value);
  void add_bytes_type(const char* value);
  void add_bytes_type(const void* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& bytes_type() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_bytes_type();
  private:
  const std::string& _internal_bytes_type(int index) const;
  std::string* _internal_add_bytes_type();
  public:

  // @@protoc_insertion_point(class_scope:ezcom.ProtobufMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< double > double_type_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< float > float_type_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t > int32_type_;
  mutable std::atomic<int> _int32_type_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int64_t > int64_type_;
  mutable std::atomic<int> _int64_type_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t > uint32_type_;
  mutable std::atomic<int> _uint32_type_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint64_t > uint64_type_;
  mutable std::atomic<int> _uint64_type_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool > bool_type_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> string_type_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> bytes_type_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ezcom_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ProtobufMessage

// repeated double double_type = 1;
inline int ProtobufMessage::_internal_double_type_size() const {
  return double_type_.size();
}
inline int ProtobufMessage::double_type_size() const {
  return _internal_double_type_size();
}
inline void ProtobufMessage::clear_double_type() {
  double_type_.Clear();
}
inline double ProtobufMessage::_internal_double_type(int index) const {
  return double_type_.Get(index);
}
inline double ProtobufMessage::double_type(int index) const {
  // @@protoc_insertion_point(field_get:ezcom.ProtobufMessage.double_type)
  return _internal_double_type(index);
}
inline void ProtobufMessage::set_double_type(int index, double value) {
  double_type_.Set(index, value);
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.double_type)
}
inline void ProtobufMessage::_internal_add_double_type(double value) {
  double_type_.Add(value);
}
inline void ProtobufMessage::add_double_type(double value) {
  _internal_add_double_type(value);
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.double_type)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >&
ProtobufMessage::_internal_double_type() const {
  return double_type_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >&
ProtobufMessage::double_type() const {
  // @@protoc_insertion_point(field_list:ezcom.ProtobufMessage.double_type)
  return _internal_double_type();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >*
ProtobufMessage::_internal_mutable_double_type() {
  return &double_type_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >*
ProtobufMessage::mutable_double_type() {
  // @@protoc_insertion_point(field_mutable_list:ezcom.ProtobufMessage.double_type)
  return _internal_mutable_double_type();
}

// repeated float float_type = 2;
inline int ProtobufMessage::_internal_float_type_size() const {
  return float_type_.size();
}
inline int ProtobufMessage::float_type_size() const {
  return _internal_float_type_size();
}
inline void ProtobufMessage::clear_float_type() {
  float_type_.Clear();
}
inline float ProtobufMessage::_internal_float_type(int index) const {
  return float_type_.Get(index);
}
inline float ProtobufMessage::float_type(int index) const {
  // @@protoc_insertion_point(field_get:ezcom.ProtobufMessage.float_type)
  return _internal_float_type(index);
}
inline void ProtobufMessage::set_float_type(int index, float value) {
  float_type_.Set(index, value);
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.float_type)
}
inline void ProtobufMessage::_internal_add_float_type(float value) {
  float_type_.Add(value);
}
inline void ProtobufMessage::add_float_type(float value) {
  _internal_add_float_type(value);
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.float_type)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< float >&
ProtobufMessage::_internal_float_type() const {
  return float_type_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< float >&
ProtobufMessage::float_type() const {
  // @@protoc_insertion_point(field_list:ezcom.ProtobufMessage.float_type)
  return _internal_float_type();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< float >*
ProtobufMessage::_internal_mutable_float_type() {
  return &float_type_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< float >*
ProtobufMessage::mutable_float_type() {
  // @@protoc_insertion_point(field_mutable_list:ezcom.ProtobufMessage.float_type)
  return _internal_mutable_float_type();
}

// repeated int32 int32_type = 3;
inline int ProtobufMessage::_internal_int32_type_size() const {
  return int32_type_.size();
}
inline int ProtobufMessage::int32_type_size() const {
  return _internal_int32_type_size();
}
inline void ProtobufMessage::clear_int32_type() {
  int32_type_.Clear();
}
inline int32_t ProtobufMessage::_internal_int32_type(int index) const {
  return int32_type_.Get(index);
}
inline int32_t ProtobufMessage::int32_type(int index) const {
  // @@protoc_insertion_point(field_get:ezcom.ProtobufMessage.int32_type)
  return _internal_int32_type(index);
}
inline void ProtobufMessage::set_int32_type(int index, int32_t value) {
  int32_type_.Set(index, value);
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.int32_type)
}
inline void ProtobufMessage::_internal_add_int32_type(int32_t value) {
  int32_type_.Add(value);
}
inline void ProtobufMessage::add_int32_type(int32_t value) {
  _internal_add_int32_type(value);
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.int32_type)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
ProtobufMessage::_internal_int32_type() const {
  return int32_type_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
ProtobufMessage::int32_type() const {
  // @@protoc_insertion_point(field_list:ezcom.ProtobufMessage.int32_type)
  return _internal_int32_type();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
ProtobufMessage::_internal_mutable_int32_type() {
  return &int32_type_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
ProtobufMessage::mutable_int32_type() {
  // @@protoc_insertion_point(field_mutable_list:ezcom.ProtobufMessage.int32_type)
  return _internal_mutable_int32_type();
}

// repeated int64 int64_type = 4;
inline int ProtobufMessage::_internal_int64_type_size() const {
  return int64_type_.size();
}
inline int ProtobufMessage::int64_type_size() const {
  return _internal_int64_type_size();
}
inline void ProtobufMessage::clear_int64_type() {
  int64_type_.Clear();
}
inline int64_t ProtobufMessage::_internal_int64_type(int index) const {
  return int64_type_.Get(index);
}
inline int64_t ProtobufMessage::int64_type(int index) const {
  // @@protoc_insertion_point(field_get:ezcom.ProtobufMessage.int64_type)
  return _internal_int64_type(index);
}
inline void ProtobufMessage::set_int64_type(int index, int64_t value) {
  int64_type_.Set(index, value);
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.int64_type)
}
inline void ProtobufMessage::_internal_add_int64_type(int64_t value) {
  int64_type_.Add(value);
}
inline void ProtobufMessage::add_int64_type(int64_t value) {
  _internal_add_int64_type(value);
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.int64_type)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int64_t >&
ProtobufMessage::_internal_int64_type() const {
  return int64_type_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int64_t >&
ProtobufMessage::int64_type() const {
  // @@protoc_insertion_point(field_list:ezcom.ProtobufMessage.int64_type)
  return _internal_int64_type();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int64_t >*
ProtobufMessage::_internal_mutable_int64_type() {
  return &int64_type_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int64_t >*
ProtobufMessage::mutable_int64_type() {
  // @@protoc_insertion_point(field_mutable_list:ezcom.ProtobufMessage.int64_type)
  return _internal_mutable_int64_type();
}

// repeated uint32 uint32_type = 5;
inline int ProtobufMessage::_internal_uint32_type_size() const {
  return uint32_type_.size();
}
inline int ProtobufMessage::uint32_type_size() const {
  return _internal_uint32_type_size();
}
inline void ProtobufMessage::clear_uint32_type() {
  uint32_type_.Clear();
}
inline uint32_t ProtobufMessage::_internal_uint32_type(int index) const {
  return uint32_type_.Get(index);
}
inline uint32_t ProtobufMessage::uint32_type(int index) const {
  // @@protoc_insertion_point(field_get:ezcom.ProtobufMessage.uint32_type)
  return _internal_uint32_type(index);
}
inline void ProtobufMessage::set_uint32_type(int index, uint32_t value) {
  uint32_type_.Set(index, value);
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.uint32_type)
}
inline void ProtobufMessage::_internal_add_uint32_type(uint32_t value) {
  uint32_type_.Add(value);
}
inline void ProtobufMessage::add_uint32_type(uint32_t value) {
  _internal_add_uint32_type(value);
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.uint32_type)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
ProtobufMessage::_internal_uint32_type() const {
  return uint32_type_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
ProtobufMessage::uint32_type() const {
  // @@protoc_insertion_point(field_list:ezcom.ProtobufMessage.uint32_type)
  return _internal_uint32_type();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
ProtobufMessage::_internal_mutable_uint32_type() {
  return &uint32_type_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
ProtobufMessage::mutable_uint32_type() {
  // @@protoc_insertion_point(field_mutable_list:ezcom.ProtobufMessage.uint32_type)
  return _internal_mutable_uint32_type();
}

// repeated uint64 uint64_type = 6;
inline int ProtobufMessage::_internal_uint64_type_size() const {
  return uint64_type_.size();
}
inline int ProtobufMessage::uint64_type_size() const {
  return _internal_uint64_type_size();
}
inline void ProtobufMessage::clear_uint64_type() {
  uint64_type_.Clear();
}
inline uint64_t ProtobufMessage::_internal_uint64_type(int index) const {
  return uint64_type_.Get(index);
}
inline uint64_t ProtobufMessage::uint64_type(int index) const {
  // @@protoc_insertion_point(field_get:ezcom.ProtobufMessage.uint64_type)
  return _internal_uint64_type(index);
}
inline void ProtobufMessage::set_uint64_type(int index, uint64_t value) {
  uint64_type_.Set(index, value);
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.uint64_type)
}
inline void ProtobufMessage::_internal_add_uint64_type(uint64_t value) {
  uint64_type_.Add(value);
}
inline void ProtobufMessage::add_uint64_type(uint64_t value) {
  _internal_add_uint64_type(value);
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.uint64_type)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint64_t >&
ProtobufMessage::_internal_uint64_type() const {
  return uint64_type_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint64_t >&
ProtobufMessage::uint64_type() const {
  // @@protoc_insertion_point(field_list:ezcom.ProtobufMessage.uint64_type)
  return _internal_uint64_type();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint64_t >*
ProtobufMessage::_internal_mutable_uint64_type() {
  return &uint64_type_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint64_t >*
ProtobufMessage::mutable_uint64_type() {
  // @@protoc_insertion_point(field_mutable_list:ezcom.ProtobufMessage.uint64_type)
  return _internal_mutable_uint64_type();
}

// repeated bool bool_type = 7;
inline int ProtobufMessage::_internal_bool_type_size() const {
  return bool_type_.size();
}
inline int ProtobufMessage::bool_type_size() const {
  return _internal_bool_type_size();
}
inline void ProtobufMessage::clear_bool_type() {
  bool_type_.Clear();
}
inline bool ProtobufMessage::_internal_bool_type(int index) const {
  return bool_type_.Get(index);
}
inline bool ProtobufMessage::bool_type(int index) const {
  // @@protoc_insertion_point(field_get:ezcom.ProtobufMessage.bool_type)
  return _internal_bool_type(index);
}
inline void ProtobufMessage::set_bool_type(int index, bool value) {
  bool_type_.Set(index, value);
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.bool_type)
}
inline void ProtobufMessage::_internal_add_bool_type(bool value) {
  bool_type_.Add(value);
}
inline void ProtobufMessage::add_bool_type(bool value) {
  _internal_add_bool_type(value);
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.bool_type)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >&
ProtobufMessage::_internal_bool_type() const {
  return bool_type_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >&
ProtobufMessage::bool_type() const {
  // @@protoc_insertion_point(field_list:ezcom.ProtobufMessage.bool_type)
  return _internal_bool_type();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >*
ProtobufMessage::_internal_mutable_bool_type() {
  return &bool_type_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >*
ProtobufMessage::mutable_bool_type() {
  // @@protoc_insertion_point(field_mutable_list:ezcom.ProtobufMessage.bool_type)
  return _internal_mutable_bool_type();
}

// repeated string string_type = 8;
inline int ProtobufMessage::_internal_string_type_size() const {
  return string_type_.size();
}
inline int ProtobufMessage::string_type_size() const {
  return _internal_string_type_size();
}
inline void ProtobufMessage::clear_string_type() {
  string_type_.Clear();
}
inline std::string* ProtobufMessage::add_string_type() {
  std::string* _s = _internal_add_string_type();
  // @@protoc_insertion_point(field_add_mutable:ezcom.ProtobufMessage.string_type)
  return _s;
}
inline const std::string& ProtobufMessage::_internal_string_type(int index) const {
  return string_type_.Get(index);
}
inline const std::string& ProtobufMessage::string_type(int index) const {
  // @@protoc_insertion_point(field_get:ezcom.ProtobufMessage.string_type)
  return _internal_string_type(index);
}
inline std::string* ProtobufMessage::mutable_string_type(int index) {
  // @@protoc_insertion_point(field_mutable:ezcom.ProtobufMessage.string_type)
  return string_type_.Mutable(index);
}
inline void ProtobufMessage::set_string_type(int index, const std::string& value) {
  string_type_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.string_type)
}
inline void ProtobufMessage::set_string_type(int index, std::string&& value) {
  string_type_.Mutable(index)->assign(std::move(value));
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.string_type)
}
inline void ProtobufMessage::set_string_type(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  string_type_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:ezcom.ProtobufMessage.string_type)
}
inline void ProtobufMessage::set_string_type(int index, const char* value, size_t size) {
  string_type_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:ezcom.ProtobufMessage.string_type)
}
inline std::string* ProtobufMessage::_internal_add_string_type() {
  return string_type_.Add();
}
inline void ProtobufMessage::add_string_type(const std::string& value) {
  string_type_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.string_type)
}
inline void ProtobufMessage::add_string_type(std::string&& value) {
  string_type_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.string_type)
}
inline void ProtobufMessage::add_string_type(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  string_type_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:ezcom.ProtobufMessage.string_type)
}
inline void ProtobufMessage::add_string_type(const char* value, size_t size) {
  string_type_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:ezcom.ProtobufMessage.string_type)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
ProtobufMessage::string_type() const {
  // @@protoc_insertion_point(field_list:ezcom.ProtobufMessage.string_type)
  return string_type_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
ProtobufMessage::mutable_string_type() {
  // @@protoc_insertion_point(field_mutable_list:ezcom.ProtobufMessage.string_type)
  return &string_type_;
}

// repeated bytes bytes_type = 9;
inline int ProtobufMessage::_internal_bytes_type_size() const {
  return bytes_type_.size();
}
inline int ProtobufMessage::bytes_type_size() const {
  return _internal_bytes_type_size();
}
inline void ProtobufMessage::clear_bytes_type() {
  bytes_type_.Clear();
}
inline std::string* ProtobufMessage::add_bytes_type() {
  std::string* _s = _internal_add_bytes_type();
  // @@protoc_insertion_point(field_add_mutable:ezcom.ProtobufMessage.bytes_type)
  return _s;
}
inline const std::string& ProtobufMessage::_internal_bytes_type(int index) const {
  return bytes_type_.Get(index);
}
inline const std::string& ProtobufMessage::bytes_type(int index) const {
  // @@protoc_insertion_point(field_get:ezcom.ProtobufMessage.bytes_type)
  return _internal_bytes_type(index);
}
inline std::string* ProtobufMessage::mutable_bytes_type(int index) {
  // @@protoc_insertion_point(field_mutable:ezcom.ProtobufMessage.bytes_type)
  return bytes_type_.Mutable(index);
}
inline void ProtobufMessage::set_bytes_type(int index, const std::string& value) {
  bytes_type_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.bytes_type)
}
inline void ProtobufMessage::set_bytes_type(int index, std::string&& value) {
  bytes_type_.Mutable(index)->assign(std::move(value));
  // @@protoc_insertion_point(field_set:ezcom.ProtobufMessage.bytes_type)
}
inline void ProtobufMessage::set_bytes_type(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  bytes_type_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:ezcom.ProtobufMessage.bytes_type)
}
inline void ProtobufMessage::set_bytes_type(int index, const void* value, size_t size) {
  bytes_type_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:ezcom.ProtobufMessage.bytes_type)
}
inline std::string* ProtobufMessage::_internal_add_bytes_type() {
  return bytes_type_.Add();
}
inline void ProtobufMessage::add_bytes_type(const std::string& value) {
  bytes_type_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.bytes_type)
}
inline void ProtobufMessage::add_bytes_type(std::string&& value) {
  bytes_type_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:ezcom.ProtobufMessage.bytes_type)
}
inline void ProtobufMessage::add_bytes_type(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  bytes_type_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:ezcom.ProtobufMessage.bytes_type)
}
inline void ProtobufMessage::add_bytes_type(const void* value, size_t size) {
  bytes_type_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:ezcom.ProtobufMessage.bytes_type)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
ProtobufMessage::bytes_type() const {
  // @@protoc_insertion_point(field_list:ezcom.ProtobufMessage.bytes_type)
  return bytes_type_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
ProtobufMessage::mutable_bytes_type() {
  // @@protoc_insertion_point(field_mutable_list:ezcom.ProtobufMessage.bytes_type)
  return &bytes_type_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace ezcom

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ezcom_2eproto
