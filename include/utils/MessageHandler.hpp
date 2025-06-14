#pragma once

#include <iostream>
#include <string>

namespace utils {

class MessageHandler {
 public:
  static void logError(const std::string& context, const std::exception& error);
  static void logError(const std::string& message);

  static void logWarning(const std::string& message);

  static void logSuccess(const std::string& message);

  static void logMessage(const std::string& message);
};

}  // namespace utils
