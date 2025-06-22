#include "utils/ExceptionHandler.hpp"

#include <iostream>

#include "enums/Enums.hpp"
#include "exceptions/Exception.hpp"
#include "utils/MessageHandler.hpp"

namespace utils {

void ExceptionHandler::handleException(const std::exception& e) {
  const exceptions::BaseException* baseException =
      dynamic_cast<const exceptions::BaseException*>(&e);

  if (baseException) {
    switch (baseException->getType()) {
      case enums::ExceptionType::VALIDATION_ERROR:
        utils::MessageHandler::logError("Lỗi xác thực: " +
                                        std::string(e.what()));
        break;

      case enums::ExceptionType::AUTH_ERROR:
        utils::MessageHandler::logError("Lỗi xác thực: " +
                                        std::string(e.what()));
        break;

      case enums::ExceptionType::STORAGE_ERROR:
        utils::MessageHandler::logError("Lỗi lưu trữ: " +
                                        std::string(e.what()));
        break;

      case enums::ExceptionType::NOT_FOUND_ERROR:
        utils::MessageHandler::logError("Không tìm thấy: " +
                                        std::string(e.what()));
        break;

      default:
        utils::MessageHandler::logError("Lỗi không xác định: " +
                                        std::string(e.what()));
        break;
    }
  } else {
    utils::MessageHandler::logError("Lỗi hệ thống: " + std::string(e.what()));
  }
}

}  // namespace utils