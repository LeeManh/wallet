#include "models/Otp.hpp"

#include <ctime>

#include "enums/Enums.hpp"

namespace models {

// Constructor
OTP::OTP(const int id, const int userId, const std::string& otpCode,
         const enums::OTPType& otpType)
    : id(id), userId(userId), otpCode(otpCode), otpType(otpType) {
  time_t now = time(nullptr);
  expiresAt = now + 300;  // Mặc định hết hạn sau 5 phút
}

// Getters
int OTP::getId() const { return id; }
int OTP::getUserId() const { return userId; }
std::string OTP::getOtpCode() const { return otpCode; }
enums::OTPType OTP::getOtpType() const { return otpType; }
time_t OTP::getExpiresAt() const { return expiresAt; }

// Setters
void OTP::setOtpCode(const std::string& newOtpCode) { otpCode = newOtpCode; }
void OTP::setExpiresAt(const time_t& newExpiresAt) { expiresAt = newExpiresAt; }

}  // namespace models