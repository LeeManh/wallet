#include "controllers/AuthController.hpp"

#include <iostream>
#include <tuple>

#include "services/OtpService.hpp"
#include "utils/MessageHandler.hpp"

namespace controllers {

std::tuple<bool, int, bool> AuthController::login(const std::string& username,
                                                  const std::string& password) {
  return authService.login(username, password);
}

bool AuthController::registerUser(const std::string& username,
                                  const std::string& password,
                                  const std::string& email,
                                  const std::string& fullName) {
  return authService.registerUser(username, password, email, fullName);
}

bool AuthController::registerUserByAdmin(const std::string& username,
                                         const std::string& email,
                                         const std::string& fullName,
                                         std::string& generatedPassword) {
  return authService.registerUserByAdmin(username, email, fullName,
                                         generatedPassword);
}

bool AuthController::changePassword(const int userId,
                                    const std::string& currentPassword,
                                    const std::string& newPassword) {
  return authService.changePassword(userId, currentPassword, newPassword);
}

bool AuthController::sendOTPInfoChange(const int userId) {
  try {
    std::string email = userService.getUserEmail(userId);
    if (email.empty()) {
      utils::MessageHandler::logError("Không tìm thấy email của người dùng!");
      return false;
    }
    return services::OtpService::generateAndSendOTP(userId, email);
  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi gửi OTP: " +
                                    std::string(e.what()));
    return false;
  }
}

bool AuthController::verifyOTPAndChangePassword(
    const int userId, const std::string& otpCode,
    const std::string& currentPassword, const std::string& newPassword) {
  try {
    if (!services::OtpService::verifyOTP(userId, otpCode,
                                         models::OTPType::INFO_CHANGE)) {
      return false;
    }
    return authService.changePassword(userId, currentPassword, newPassword);
  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi xác thực OTP và đổi mật khẩu: " +
                                    std::string(e.what()));
    return false;
  }
}

}  // namespace controllers