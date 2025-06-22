#pragma once

namespace enums {

enum class ExceptionType {
  AUTH_ERROR,
  VALIDATION_ERROR,
  NOT_FOUND_ERROR,
  STORAGE_ERROR,
  UNKNOWN_ERROR
};

enum class OTPType {
  INFO_CHANGE,
};

enum class TransactionStatus {
  PENDING,    // Đang chờ xử lý
  COMPLETED,  // Hoàn thành
  FAILED,     // Thất bại
  CANCELLED   // Đã hủy
};

enum class WalletType {
  USER,
  SYSTEM,
};

}  // namespace enums