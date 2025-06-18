#pragma once

#include <stdexcept>

#include "exceptions/Exception.hpp"

namespace utils {

class ExceptionHandler {
 public:
  static void handleException(const std::exception& e);

 private:
  static void handleBaseException(const exceptions::BaseException& e);
};

}  // namespace utils