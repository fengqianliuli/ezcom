#pragma once

#include <stdexcept>

namespace ezcom {

class Exception : public std::runtime_error {
 public:
  Exception(const std::string& msg) : std::runtime_error(msg) {}
};

class InvalidParamException : public Exception {
 public:
  InvalidParamException(const std::string& msg) : Exception(msg) {}
};

class ResourceException : public Exception {
 public:
  ResourceException(const std::string& msg) : Exception(msg) {}
};

class AlreadyDoneException : public Exception {
 public:
  AlreadyDoneException(const std::string& msg) : Exception(msg) {}
};

}  // namespace ezcom
