#include "controllers/AuthController.hpp"

#include <iostream>
#include <tuple>

#include "services/AuthService.hpp"
#include "services/OtpService.hpp"
#include "services/UserService.hpp"
#include "utils/ExceptionHandler.hpp"
#include "utils/MessageHandler.hpp"

namespace controllers {

std::tuple<bool, int, bool> AuthController::login(const std::string& username,
                                                  const std::string& password) {
  try {
    auto response = services::AuthService::login(username, password);
    utils::MessageHandler::logSuccess("Đăng nhập thành công");
    return response;
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return {false, -1, false};
  }
}

void AuthController::registerUser(const std::string& username,
                                  const std::string& password,
                                  const std::string& email,
                                  const std::string& fullName) {
  try {
    services::AuthService::registerUser(username, password, email, fullName);
    utils::MessageHandler::logSuccess("Đăng ký thành công!");
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

void AuthController::registerUserByAdmin(const std::string& username,
                                         const std::string& email,
                                         const std::string& fullName,
                                         std::string& generatedPassword) {
  try {
    services::AuthService::registerUserByAdmin(username, email, fullName,
                                               generatedPassword);
    utils::MessageHandler::logSuccess("\nTạo tài khoản thành công!");
    utils::MessageHandler::logMessage("Tên đăng nhập: " + username);
    utils::MessageHandler::logMessage("Email: " + email);
    utils::MessageHandler::logMessage("Mật khẩu: " + generatedPassword);
    utils::MessageHandler::logMessage(
        "Vui lòng lưu lại mật khẩu này để đăng nhập lần đầu!");
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

void AuthController::sendOTPInfoChange(const int userId) {
  try {
    std::string email = services::UserService::getUserEmail(userId);
    if (email.empty())
      throw exceptions::NotFoundException("Email không tồn tại!");

    services::OtpService::generateAndSendOTP(userId, email);
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

void AuthController::verifyOTPAndChangePassword(
    const int userId, const std::string& otpCode,
    const std::string& currentPassword, const std::string& newPassword) {
  try {
    services::OtpService::verifyOTP(userId, otpCode,
                                    models::OTPType::INFO_CHANGE);
    services::AuthService::changePassword(userId, currentPassword, newPassword);

    // Ỉn ra kết quả thành công
    utils::MessageHandler::logSuccess("Đổi mật khẩu thành công!");
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

}  // namespace controllers