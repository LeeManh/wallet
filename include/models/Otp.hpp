#ifndef OTP_HPP
#define OTP_HPP

#include <string>

namespace models {

enum class OTPType {
  INFO_CHANGE,
};

class OTP {
 private:
  int id;
  int userId;
  std::string otpCode;
  OTPType otpType;
  time_t createdAt;
  time_t expiresAt;

 public:
  OTP(const int id, const int userId, const std::string& otpCode,
      const OTPType& otpType);

  // Getters
  int getId() const;
  int getUserId() const;
  std::string getOtpCode() const;
  OTPType getOtpType() const;
  time_t getCreatedAt() const;
  time_t getExpiresAt() const;

  // Setters
  void setOtpCode(const std::string& newOtpCode);
  void setExpiresAt(const time_t& newExpiresAt);
};

}  // namespace models

#endif