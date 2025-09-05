#include "utils/ExceptionHandler.hpp"

#include <iostream>

#include "enums/Enums.hpp"
#include "exceptions/Exception.hpp"
#include "utils/MessageHandler.hpp"

namespace utils {

/**
 * @brief Xử lý và phân loại exception, in ra thông báo lỗi phù hợp.
 *
 * Input:
 *   - e: Đối tượng exception cần xử lý.
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Thông báo lỗi được in ra log theo từng loại lỗi cụ thể.
 *
 * Thủ tục xử lý:
 *   1. Thử ép kiểu exception thành BaseException (exception tuỳ chỉnh trong hệ thống).
 *   2. Nếu là BaseException:
 *        - Dựa vào getType() để phân loại:
 *            + VALIDATION_ERROR → in "Lỗi xác thực".
 *            + AUTH_ERROR → in "Lỗi xác thực".
 *            + STORAGE_ERROR → in "Lỗi lưu trữ".
 *            + NOT_FOUND_ERROR → in "Không tìm thấy".
 *            + Loại khác → in "Lỗi không xác định".
 *        - Kèm theo thông tin chi tiết từ e.what().
 *   3. Nếu không phải BaseException (exception chuẩn C++):
 *        - In "Lỗi hệ thống" kèm theo e.what().
 */
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