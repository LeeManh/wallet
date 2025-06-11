#include "models/Otp.hpp"

#include <ctime>

namespace models {

// Constructor
OTP::OTP(const int id, const int userId, const std::string& otpCode,
         const OTPType& otpType)
    : id(id), userId(userId), otpCode(otpCode), otpType(otpType) {
  createdAt = time(nullptr);
  expiresAt = createdAt + 300;  // Mặc định hết hạn sau 5 phút
}

// Getters
int OTP::getId() const { return id; }
int OTP::getUserId() const { return userId; }
std::string OTP::getOtpCode() const { return otpCode; }
OTPType OTP::getOtpType() const { return otpType; }
time_t OTP::getCreatedAt() const { return createdAt; }
time_t OTP::getExpiresAt() const { return expiresAt; }

// Setters
void OTP::setOtpCode(const std::string& newOtpCode) { otpCode = newOtpCode; }
void OTP::setExpiresAt(const time_t& newExpiresAt) { expiresAt = newExpiresAt; }

}  // namespace models