#pragma once

#include <stdexcept>
#include <string>

#include "exceptions/ExceptionType.hpp"

namespace exceptions {

class BaseException : public std::exception {
 protected:
  ExceptionType type;
  std::string msg;

 public:
  BaseException(ExceptionType type, const std::string& msg);
  const char* what() const noexcept override;
  ExceptionType getType() const;
};

class AuthException : public BaseException {
 public:
  explicit AuthException(const std::string& msg);
};

class ValidationException : public BaseException {
 public:
  explicit ValidationException(const std::string& msg);
};

class NotFoundException : public BaseException {
 public:
  explicit NotFoundException(const std::string& msg);
};

class StorageException : public BaseException {
 public:
  explicit StorageException(const std::string& msg);
};

class UnknownException : public BaseException {
 public:
  explicit UnknownException(const std::string& msg);
};

}  // namespace exceptions