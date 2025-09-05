#include "exceptions/Exception.hpp"

#include "enums/Enums.hpp"

namespace exceptions {
    
/**
 * @class BaseException
 * @brief Lớp cơ sở cho toàn bộ hệ thống ngoại lệ trong dự án.
 *
 * Input:
 *   - type: Kiểu ngoại lệ (enums::ExceptionType).
 *   - msg: Thông báo lỗi chi tiết.
 *
 * Output:
 *   - Cung cấp thông tin kiểu ngoại lệ và nội dung lỗi khi xảy ra.
 *
 * Thủ tục xử lý:
 *   1. Lưu trữ type và msg khi khởi tạo.
 *   2. Cho phép lấy lại type qua getType().
 *   3. Ghi đè hàm what() để trả về chuỗi thông báo lỗi (chuẩn C++).
 */
BaseException::BaseException(enums::ExceptionType type, const std::string& msg)
    : type(type), msg(msg) {}

enums::ExceptionType BaseException::getType() const { return type; }

const char* BaseException::what() const noexcept { return msg.c_str(); }

/**
 * @class AuthException
 * @brief Ngoại lệ cho các lỗi xác thực (login, đăng ký, quyền truy cập...).
 */
AuthException::AuthException(const std::string& msg)
    : BaseException(enums::ExceptionType::AUTH_ERROR, msg) {}

/**
 * @class ValidationException
 * @brief Ngoại lệ cho các lỗi kiểm tra dữ liệu (đầu vào không hợp lệ...).
 */    
ValidationException::ValidationException(const std::string& msg)
    : BaseException(enums::ExceptionType::VALIDATION_ERROR, msg) {}

/**
 * @class NotFoundException
 * @brief Ngoại lệ cho các lỗi không tìm thấy dữ liệu (user, ví...).
 */
NotFoundException::NotFoundException(const std::string& msg)
    : BaseException(enums::ExceptionType::NOT_FOUND_ERROR, msg) {}

/**
 * @class StorageException
 * @brief Ngoại lệ cho các lỗi lưu trữ (đọc/ghi file, database...).
 */
StorageException::StorageException(const std::string& msg)
    : BaseException(enums::ExceptionType::STORAGE_ERROR, msg) {}

/**
 * @class TransactionException
 * @brief Ngoại lệ cho các lỗi liên quan đến giao dịch (chuyển điểm, rollback...).
 */
TransactionException::TransactionException(const std::string& msg)
    : BaseException(enums::ExceptionType::TRANSACTION_ERROR, msg) {}

}  // namespace exceptions