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

enum class WalletInfo {
  POINT,
  WALLET_ID,
  USER_ID,
  WALLET_TYPE
};
enum class CellSize {
  ID = 2,
  WALLET_ID = 10,
  USER_ID = 10,
  USERNAME = 15,
  EMAIL = 23,
  FULL_NAME = 23,
  WALLET_TYPE = 10,
  POINT = 10
};
}  // namespace enums