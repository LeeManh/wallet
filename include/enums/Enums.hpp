#pragma once
#include <string>

namespace enums {

enum class ExceptionType {
  AUTH_ERROR,
  VALIDATION_ERROR,
  NOT_FOUND_ERROR,
  STORAGE_ERROR,
  UNKNOWN_ERROR,
  TRANSACTION_ERROR,
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

enum class UserInfo {
  USERNAME,
  EMAIL,
  FULL_NAME,
  ID,
};

enum class CellSize {
  ID = 2,
  USERNAME = 15,
  EMAIL = 23,
  FULL_NAME = 23,
};

inline std::string to_string(UserInfo info) {
  switch (info) {
    case UserInfo::USERNAME: return "Tên đăng nhập";
    case UserInfo::EMAIL: return "Email";
    case UserInfo::FULL_NAME: return "Họ và tên";
    case UserInfo::ID: return "ID";
    default: return "UNKNOWN";
  }
}

inline int getCellSize(UserInfo info) {
    switch (info) {
        case UserInfo::ID: return static_cast<int>(CellSize::ID);
        case UserInfo::USERNAME: return static_cast<int>(CellSize::USERNAME);
        case UserInfo::EMAIL: return static_cast<int>(CellSize::EMAIL);
        case UserInfo::FULL_NAME: return static_cast<int>(CellSize::FULL_NAME);
        default: return 0;
    }
}
}  // namespace enums