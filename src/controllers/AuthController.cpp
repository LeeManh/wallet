#include "controllers/AuthController.hpp"

#include <iostream>
#include <string>
#include <tuple>

#include "enums/Enums.hpp"
#include "services/AuthService.hpp"
#include "services/OtpService.hpp"
#include "services/UserService.hpp"
#include "utils/ExceptionHandler.hpp"
#include "utils/Input.hpp"
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
    utils::MessageHandler::logMessage("\n");
    utils::MessageHandler::logSuccess("Tạo tài khoản thành công!");
    utils::MessageHandler::logMessage("Tên đăng nhập: " + username);
    utils::MessageHandler::logMessage("Email: " + email);
    utils::MessageHandler::logMessage("Mật khẩu: " + generatedPassword);
    utils::MessageHandler::logMessage(
        "Vui lòng lưu lại mật khẩu này để đăng nhập lần đầu!");
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

void AuthController::changePasswordWithOTP(const int userId,
                                           const std::string& currentPassword,
                                           const std::string& newPassword) {
  try {
    auto userJson = services::UserService::findUserById(userId);
    std::string email = userJson.value()["email"];

    if (!userJson.has_value())
      throw exceptions::NotFoundException("Email không tồn tại!");

    // Input OTP
    utils::MessageHandler::logMessage("\nGửi mã OTP để xác thực...");
    services::OtpService::generateAndSendOTP(userId, email,
                                             enums::OTPType::INFO_CHANGE);

    // Tạo và xác minh OTP
    std::string otpCode = utils::input::getInput("Nhập mã OTP đã được gửi: ");
    services::OtpService::verifyOTP(userId, otpCode,
                                    enums::OTPType::INFO_CHANGE);

    // Message thành công
    utils::MessageHandler::logMessage("Đổi mật khẩu thành công.");
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}
}  // namespace controllers