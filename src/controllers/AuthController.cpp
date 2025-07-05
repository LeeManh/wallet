#include "controllers/AuthController.hpp"

#include <iostream>
#include <string>
#include <tuple>
#include <sstream>

#include "enums/Enums.hpp"
#include "services/AuthService.hpp"
#include "services/OtpService.hpp"
#include "services/UserService.hpp"
#include "utils/ExceptionHandler.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"
#include "utils/Format.hpp"

namespace controllers {

std::tuple<bool, int, bool, bool> AuthController::login(const std::string& username,
                                                  const std::string& password) {
  try {
    auto response = services::AuthService::login(username, password);
    utils::MessageHandler::logSuccess("Đăng nhập thành công");
    return response;
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return {false, -1, false, false};
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
void AuthController::getProfile(const int userId) {
  try {
    auto userJson = services::UserService::findUserById(userId);
    if (!userJson.has_value())
      throw exceptions::NotFoundException("Người dùng không tồn tại!");

    utils::MessageHandler::logMessage("Thông tin người dùng:");
    utils::MessageHandler::logMessage("Họ tên: " + std::string(userJson.value()["fullName"]));
    utils::MessageHandler::logMessage("Email: " + std::string(userJson.value()["email"]));
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}
void AuthController::printListUsers(std::vector<models::User> users) {
  try {
    utils::MessageHandler::logMessage(
      "+----+----------------+------------------------+------------------------+");
    utils::MessageHandler::logMessage(
      "| ID | Tên đăng nhập  | Email                  | Họ tên                 |");
    utils::MessageHandler::logMessage(
      "+----+----------------+------------------------+------------------------+");
    for (const auto& user : users) {
      std::ostringstream oss;
      oss << "| "
        << std::setw(2) << std::left << user.getId() << " "
        << "| " << utils::format::formatCell(user.getUsername(), 15)
        << "| " << utils::format::formatCell(user.getEmail(), 23)
        << "| " << utils::format::formatCell(user.getFullName(), 23)
        << "|";
      utils::MessageHandler::logMessage(oss.str());
    }
    utils::MessageHandler::logMessage(
      "+----+----------------+------------------------+------------------------+");
  }
  catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

void AuthController::updateProfile(const int userId,
                                   const std::string& newFullName,
                                   const std::string& newEmail) {
  try {
    services::AuthService::editUserInfo(userId, newFullName, newEmail);
    utils::MessageHandler::logSuccess("Cập nhật thông tin thành công!");
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

void AuthController::editUserInfoByAdmin(const int userId,
                                   const std::string& newFullName,
                                  const std::string& newEmail){
  try {
    services::AuthService::editUserInfo(userId, newFullName, newEmail);
    utils::MessageHandler::logSuccess("Cập nhật thông tin người dùng thành công!");
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
};


void AuthController::changePasswordWithOTP(const int userId,
                                           const std::string& currentPassword,
                                           const std::string& newPassword) {
  try {
    auto userJson = services::UserService::findUserById(userId);
    std::string email = userJson.value()["email"];

    if (!userJson.has_value())
      throw exceptions::NotFoundException("Email không tồn tại!");

    // Input OTP
    utils::MessageHandler::logMessage("Gửi mã OTP để xác thực...");
    services::OtpService::generateAndSendOTP(userId, email,
                                             enums::OTPType::INFO_CHANGE);

    // Tạo và xác minh OTP
    std::string otpCode = utils::input::getInput("Nhập mã OTP đã được gửi: ");
    utils::MessageHandler::logMessage(
        "───────────────────────────────────────────────");

    services::OtpService::verifyOTP(userId, otpCode,
                                    enums::OTPType::INFO_CHANGE);

    // Cập nhật mật khẩu mới
    services::AuthService::updateUserPassword(userId, newPassword);

    // Message thành công
    utils::MessageHandler::logSuccess("Đổi mật khẩu thành công.");
  } catch (const std::exception& e) {
    utils::MessageHandler::logMessage(
        "───────────────────────────────────────────────");
    utils::ExceptionHandler::handleException(e);
  }
}
}  // namespace controllers