#include "utils/MessageHandler.hpp"

namespace utils {

void MessageHandler::logError(const std::string& context,
                              const std::exception& e) {
  std::cout << "❌ Lỗi [" << context << "]: " << e.what() << std::endl;
}

void MessageHandler::logError(const std::string& message) {
  std::cout << "❌ Lỗi: " << message << std::endl;
}

void MessageHandler::logWarning(const std::string& message) {
  std::cout << "⚠️ Cảnh báo: " << message << std::endl;
}

void MessageHandler::logSuccess(const std::string& message) {
  std::cout << "🎉 " << message << std::endl;
}

void MessageHandler::logMessage(const std::string& message) {
  std::cout << message << std::endl;
}

}  // namespace utils