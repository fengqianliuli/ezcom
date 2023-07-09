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

class ResourceInitException : public Exception {
 public:
  ResourceInitException(const std::string& msg) : Exception(msg) {}
};

}  // namespace ezcom
