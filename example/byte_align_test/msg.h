#pragma once

#include <string>

namespace ezcom {

#pragma pack(1)
struct TestMsg_t {
  int int_value;
  double double_value;
  char char_value[10];
};
#pragma pack ()

}  // namespace ezcom
