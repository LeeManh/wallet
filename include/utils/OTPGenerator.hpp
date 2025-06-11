#ifndef OTP_GENERATOR_HPP
#define OTP_GENERATOR_HPP

#include <ctime>
#include <string>

namespace utils {
namespace otp {

class OTPGenerator {
 public:
  // Tạo mã OTP mới
  static std::string generateOTP();

  // Tạo secret key cho OTP
  static std::string generateSecret();

  // Xác thực mã OTP
  static bool verifyOTP(const std::string& otp, const std::string& secret);

  // Gửi mã OTP qua email
  static bool sendOTP(const std::string& email, const std::string& otp);

  // Kiểm tra OTP đã hết hạn chưa
  static bool isOTPExpired(time_t otpTime, int expiryMinutes = 5);

  // Tạo TOTP (Time-based One-Time Password)
  static std::string generateTOTP(const std::string& secret);

  // Xác thực TOTP
  static bool verifyTOTP(const std::string& otp, const std::string& secret);

 private:
  // Chuyển đổi secret key sang định dạng base32
  static std::string toBase32(const std::string& input);
};

}  // namespace otp
}  // namespace utils

#endif  // OTP_GENERATOR_HPP