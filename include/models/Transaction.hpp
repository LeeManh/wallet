#pragma once

#include <ctime>
#include <string>

#include "enums/Enums.hpp"

namespace models {

class Transaction {
 private:
  int id;                           // Primary key
  int sourceWalletId;               // Ví nguồn
  int destinationWalletId;          // Ví đích
  double amount;                    // Số tiền giao dịch
  enums::TransactionStatus status;  // Trạng thái giao dịch
  bool otpVerified;                 // Đã xác thực OTP
  std::string otpCode;              // Mã OTP
  time_t otpExpiredAt;              // Thời gian hết hạn OTP
  time_t completedAt;               // Thời gian hoàn thành

 public:
  // Constructor
  Transaction(
      int sourceWalletId, int destinationWalletId, double amount,
      enums::TransactionStatus status = enums::TransactionStatus::PENDING,
      bool otpVerified = false, int id = -1);

  // Getters
  int getId() const;
  int getSourceWalletId() const;
  int getDestinationWalletId() const;
  double getAmount() const;
  enums::TransactionStatus getStatus() const;
  bool isOtpVerified() const;
  std::string getOtpCode() const;
  time_t getOtpExpiredAt() const;
  time_t getCompletedAt() const;

  // Setters
  void setStatus(enums::TransactionStatus newStatus);
  void setOtpVerified(bool verified);
  void setOtpCode(const std::string& code, int expiryMinutes = 5);
  void setCompletedAt(time_t time);
};

}  // namespace models
