#include "views/RegistrationView.hpp"

#include <iostream>
#include <limits>

#include "controllers/AuthController.hpp"
#include "utils/OTPGenerator.hpp"

namespace views {

void RegistrationView::display() {
  std::cout << "\n=== Đăng ký tài khoản ===" << std::endl;
}

int RegistrationView::getChoice() {
  return 0;  // Không cần xử lý choice cho view này
}

void RegistrationView::handleRegistration() {
  std::string username = getInput("Nhập tên đăng nhập: ");
  std::string password = getInput("Nhập mật khẩu: ");
  std::string confirmPassword = getInput("Nhập lại mật khẩu: ");
  std::string fullName = getInput("Nhập họ và tên: ");
  std::string email = getInput("Nhập email: ");

  if (password != confirmPassword) {
    std::cout << "Mật khẩu không khớp!" << std::endl;
    return;
  }

  // Tạo secret key cho OTP
  std::string otpSecret = utils::otp::OTPGenerator::generateSecret();

  // Tạo và gửi mã OTP
  std::string otp = utils::otp::OTPGenerator::generateTOTP(otpSecret);
  if (otp.empty()) {
    std::cout << "Không thể tạo mã OTP!" << std::endl;
    return;
  }

  std::cout << "\nMã OTP của bạn là: " << otp << std::endl;
  std::cout << "Mã này sẽ hết hạn sau 30 giây." << std::endl;

  std::string inputOTP = getInput("Nhập mã OTP để xác thực: ");

  // Xác thực OTP
  if (!utils::otp::OTPGenerator::verifyOTP(inputOTP, otpSecret)) {
    std::cout << "Mã OTP không đúng hoặc đã hết hạn!" << std::endl;
    return;
  }

  std::cout << "Xác thực OTP thành công!" << std::endl;

  // Đăng ký tài khoản
  controllers::AuthController authController;
  if (authController.registerUser(username, password, email, fullName)) {
    std::cout << "Đăng ký thành công!" << std::endl;
  }
}

}  // namespace views