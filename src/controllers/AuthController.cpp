#include "controllers/AuthController.hpp"

#include <iostream>
#include <tuple>

#include "services/AuthService.hpp"
#include "services/OtpService.hpp"
#include "services/UserService.hpp"
#include "utils/MessageHandler.hpp"

namespace controllers {

std::tuple<bool, int, bool> AuthController::login(const std::string& username,
                                                  const std::string& password) {
  return services::AuthService::login(username, password);
}

void AuthController::registerUser(const std::string& username,
                                  const std::string& password,
                                  const std::string& email,
                                  const std::string& fullName) {
  if (services::AuthService::registerUser(username, password, email,
                                          fullName)) {
    utils::MessageHandler::logSuccess("Đăng ký tài khoản thành công!");
  }
}

void AuthController::registerUserByAdmin(const std::string& username,
                                         const std::string& email,
                                         const std::string& fullName,
                                         std::string& generatedPassword) {
  if (services::AuthService::registerUserByAdmin(username, email, fullName,
                                                 generatedPassword)) {
    utils::MessageHandler::logSuccess("\nTạo tài khoản thành công!");
    utils::MessageHandler::logMessage("Tên đăng nhập: " + username);
    utils::MessageHandler::logMessage("Email: " + email);
    utils::MessageHandler::logMessage("Mật khẩu: " + generatedPassword);
    utils::MessageHandler::logMessage(
        "Vui lòng lưu lại mật khẩu này để đăng nhập lần đầu!");
  }
}

bool AuthController::changePassword(const int userId,
                                    const std::string& currentPassword,
                                    const std::string& newPassword) {
  return services::AuthService::changePassword(userId, currentPassword,
                                               newPassword);
}

void AuthController::sendOTPInfoChange(const int userId) {
  try {
    std::string email = services::UserService::getUserEmail(userId);
    if (email.empty()) {
      utils::MessageHandler::logError("Không tìm thấy email của người dùng!");
    }
    services::OtpService::generateAndSendOTP(userId, email);
  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi gửi OTP: " +
                                    std::string(e.what()));
  }
}

void AuthController::verifyOTPAndChangePassword(
    const int userId, const std::string& otpCode,
    const std::string& currentPassword, const std::string& newPassword) {
  try {
    if (!services::OtpService::verifyOTP(userId, otpCode,
                                         models::OTPType::INFO_CHANGE)) {
      utils::MessageHandler::logError("Lỗi khi xác thực OTP và đổi mật khẩu");
    }
    services::AuthService::changePassword(userId, currentPassword, newPassword);
    utils::MessageHandler::logSuccess("Đổi mật khẩu thành công!");
  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi xác thực OTP và đổi mật khẩu: " +
                                    std::string(e.what()));
  }
}

}  // namespace controllers