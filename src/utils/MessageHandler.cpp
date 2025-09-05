#include "utils/MessageHandler.hpp"

namespace utils {

/**
 * @brief Các hàm ghi log ra console với định dạng khác nhau.
 *
 * - logError: hiển thị lỗi với biểu tượng ❌
 * - logWarning: hiển thị cảnh báo với biểu tượng ⚠️
 * - logSuccess: hiển thị thành công với biểu tượng 🎉
 * - logMessage: hiển thị thông báo thường, không kèm biểu tượng
 */
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