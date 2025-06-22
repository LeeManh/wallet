#include "models/Transaction.hpp"

#include <ctime>

namespace models {

// Constructor
Transaction::Transaction(int sourceWalletId, int destinationWalletId,
                         double amount, TransactionStatus status,
                         bool otpVerified, int id)
    : id(id),
      sourceWalletId(sourceWalletId),
      destinationWalletId(destinationWalletId),
      amount(amount),
      status(status),
      otpVerified(otpVerified) {
  time_t now = time(nullptr);

  completedAt = 0;   // Chưa hoàn thành
  otpExpiredAt = 0;  // Chưa có OTP
}

// Getters
int Transaction::getId() const { return id; }
int Transaction::getSourceWalletId() const { return sourceWalletId; }
int Transaction::getDestinationWalletId() const { return destinationWalletId; }
double Transaction::getAmount() const { return amount; }
TransactionStatus Transaction::getStatus() const { return status; }
bool Transaction::isOtpVerified() const { return otpVerified; }
std::string Transaction::getOtpCode() const { return otpCode; }
time_t Transaction::getOtpExpiredAt() const { return otpExpiredAt; }
time_t Transaction::getCompletedAt() const { return completedAt; }

// Setters
void Transaction::setStatus(TransactionStatus newStatus) {
  status = newStatus;
  if (newStatus == TransactionStatus::COMPLETED) {
    completedAt = time(nullptr);
  }
}

void Transaction::setOtpVerified(bool verified) { otpVerified = verified; }

void Transaction::setOtpCode(const std::string& code, int expiryMinutes) {
  otpCode = code;
  otpExpiredAt = time(nullptr) +
                 (expiryMinutes * 60);  // Thêm số phút vào thời gian hiện tại
}

void Transaction::setCompletedAt(time_t time) { completedAt = time; }

}  // namespace models