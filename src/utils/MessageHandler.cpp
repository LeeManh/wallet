#include "utils/MessageHandler.hpp"

namespace utils {

void MessageHandler::logError(const std::string& message) {
  std::cout << "❌" << message << std::endl;
}

void MessageHandler::logWarning(const std::string& message) {
  std::cout << "⚠️" << message << std::endl;
}

void MessageHandler::logSuccess(const std::string& message) {
  std::cout << "🎉" << message << std::endl;
}

void MessageHandler::logMessage(const std::string& message) {
  std::cout << message << std::endl;
}

}  // namespace utils