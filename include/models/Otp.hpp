#pragma once

#include <string>

#include "enums/Enums.hpp"

namespace models {

class OTP {
 private:
  int id;
  int userId;
  std::string otpCode;
  enums::OTPType otpType;
  time_t expiresAt;

 public:
  OTP(const int id, const int userId, const std::string& otpCode,
      const enums::OTPType& otpType);

  // Getters
  int getId() const;
  int getUserId() const;
  std::string getOtpCode() const;
  enums::OTPType getOtpType() const;
  time_t getExpiresAt() const;

  // Setters
  void setOtpCode(const std::string& newOtpCode);
  void setExpiresAt(const time_t& newExpiresAt);
};

}  // namespace models
