#ifndef OTP_SERVICE_HPP
#define OTP_SERVICE_HPP

#include <string>

#include "models/Otp.hpp"

namespace services {

class OtpService {
 public:
  // Tạo và gửi OTP cho việc thay đổi thông tin
  static bool generateAndSendOTP(int userId, const std::string& email);

  // Xác thực OTP
  static bool verifyOTP(int userId, const std::string& otpCode,
                        models::OTPType otpType);

  // Xóa OTP đã sử dụng hoặc hết hạn
  static void cleanupExpiredOTPs();

 private:
  // Tạo mã OTP 6 chữ số
  static std::string generateOTPCode();

  // Lưu OTP vào file
  static bool saveOTP(const models::OTP& otp);

  // Đọc OTP từ file
  static std::vector<models::OTP> loadOTPs();

  // Gửi OTP qua email
  static bool sendOTPEmail(const std::string& email,
                           const std::string& otpCode);
};

}  // namespace services

#endif