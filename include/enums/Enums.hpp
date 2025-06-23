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
  TRANSFER_POINTS,
};

enum class TransactionStatus {
  PENDING,  // Đang chờ xử lý = 0
  SUCCESS,  // Thành công = 1
  FAILED,   // Thất bại = 2
};

enum class WalletType {
  USER,
  SYSTEM,
};

}  // namespace enums