#include "utils/OTPGenerator.hpp"

#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

#include "cotp.h"

namespace utils {
namespace otp {

std::string OTPGenerator::generateOTP() {
  // Tạo mã OTP 6 chữ số
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 999999);

  int otp = dis(gen);
  std::stringstream ss;
  ss << std::setw(6) << std::setfill('0') << otp;
  return ss.str();
}

std::string OTPGenerator::generateSecret() {
  // Tạo secret key 32 ký tự
  const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, chars.size() - 1);

  std::string secret;
  for (int i = 0; i < 32; ++i) {
    secret += chars[dis(gen)];
  }
  return secret;
}

std::string OTPGenerator::toBase32(const std::string& input) {
  // Chuyển đổi secret key sang định dạng base32
  // Trong trường hợp này, secret key đã được tạo với các ký tự base32
  // nên không cần chuyển đổi
  return input;
}

std::string OTPGenerator::generateTOTP(const std::string& secret) {
  // Tạo TOTP sử dụng libcotp
  cotp_error_t error_code;
  char* totp = get_totp(secret.c_str(), 6, 30, SHA1, &error_code);

  if (error_code != NO_ERROR || totp == nullptr) {
    return "";
  }

  std::string result(totp);
  free(totp);
  return result;
}

bool OTPGenerator::verifyOTP(const std::string& otp,
                             const std::string& secret) {
  // Xác thực OTP bằng cách tạo TOTP hiện tại và so sánh
  std::string currentOTP = generateTOTP(secret);
  return otp == currentOTP;
}

bool OTPGenerator::verifyTOTP(const std::string& otp,
                              const std::string& secret) {
  // Xác thực TOTP bằng cách tạo TOTP hiện tại và so sánh
  std::string currentTOTP = generateTOTP(secret);
  return otp == currentTOTP;
}

bool OTPGenerator::sendOTP(const std::string& email, const std::string& otp) {
  // TODO: Implement email sending
  // For now, just print to console
  std::cout << "Sending OTP " << otp << " to " << email << std::endl;
  return true;
}

bool OTPGenerator::isOTPExpired(time_t otpTime, int expiryMinutes) {
  time_t now = time(nullptr);
  return (now - otpTime) > (expiryMinutes * 60);
}

}  // namespace otp
}  // namespace utils