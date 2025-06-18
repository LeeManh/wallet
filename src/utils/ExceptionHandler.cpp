#include "utils/ExceptionHandler.hpp"

#include "utils/MessageHandler.hpp"

namespace utils {

void ExceptionHandler::handleException(const std::exception& e) {
  auto* baseEx = dynamic_cast<const exceptions::BaseException*>(&e);
  if (baseEx) {
    handleBaseException(*baseEx);
  } else {
    MessageHandler::logError("Lỗi không xác định: " + std::string(e.what()));
  }
}

void ExceptionHandler::handleBaseException(const exceptions::BaseException& e) {
  switch (e.getType()) {
    case exceptions::ExceptionType::VALIDATION_ERROR:
      MessageHandler::logError("Lỗi dữ liệu: " + std::string(e.what()));
      break;
    case exceptions::ExceptionType::AUTH_ERROR:
      MessageHandler::logError("Lỗi xác thực: " + std::string(e.what()));
      break;
    case exceptions::ExceptionType::STORAGE_ERROR:
      MessageHandler::logError("Lỗi lưu trữ: " + std::string(e.what()));
      break;
    default:
      MessageHandler::logError("Lỗi không xác định: " + std::string(e.what()));
      break;
  }
}

}  // namespace utils