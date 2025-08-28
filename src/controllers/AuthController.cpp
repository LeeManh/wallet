#include "controllers/AuthController.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include "enums/Enums.hpp"
#include "services/AuthService.hpp"
#include "services/OtpService.hpp"
#include "services/UserService.hpp"
#include "services/WalletService.hpp"
#include "utils/ExceptionHandler.hpp"
#include "utils/Format.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"
#include "views/UserInfoView.hpp"
#include "utils/Validation.hpp"

namespace controllers {

/**
 * @brief Xử lý đăng nhập người dùng.
 *
 * Input:
 *   - username: Tên đăng nhập.
 *   - password: Mật khẩu.
 *
 * Output:
 *   - tuple<bool, int, bool, bool>: Kết quả đăng nhập (thành công/thất bại), ID
 * người dùng, quyền admin, trạng thái mật khẩu tự động.
 *
 * Thủ tục xử lý:
 *   1. Gọi AuthService để xác thực tài khoản.
 *   2. In thông báo thành công hoặc bắt và xử lý ngoại lệ.
 */
std::tuple<bool, int, bool, bool> AuthController::login(
    const std::string& username, const std::string& password) {
  try {
    auto response = services::AuthService::login(username, password);
    utils::MessageHandler::logSuccess("Đăng nhập thành công");
    return response;
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return {false, -1, false, false};
  }
}

/**
 * @brief Đăng ký tài khoản người dùng mới.
 *
 * Input:
 *   - username: Tên đăng nhập.
 *   - password: Mật khẩu.
 *   - email: Địa chỉ email.
 *   - fullName: Họ và tên.
 *
 * Output: Không trả về giá trị, in thông báo kết quả.
 *
 * Thủ tục xử lý:
 *   1. Gọi AuthService để tạo tài khoản.
 *   2. In thông báo thành công hoặc xử lý ngoại lệ.
 */
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

/**
 * @brief Admin tạo tài khoản cho người dùng mới.
 *
 * Input:
 *   - username: Tên đăng nhập.
 *   - email: Địa chỉ email.
 *   - fullName: Họ và tên.
 *   - generatedPassword: Mật khẩu được hệ thống tạo tự động (truyền tham chiếu
 * để nhận giá trị).
 *
 * Output: Không trả về giá trị, in thông tin tài khoản mới tạo.
 *
 * Thủ tục xử lý:
 *   1. Gọi AuthService để tạo tài khoản.
 *   2. Hiển thị thông tin tài khoản và mật khẩu.
 *   3. Xử lý ngoại lệ nếu có.
 */
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

/**
 * @brief Lấy và hiển thị thông tin cá nhân của người dùng.
 *
 * Input:
 *   - userId: ID người dùng.
 *
 * Output: Không trả về giá trị, in thông tin ra màn hình.
 *
 * Thủ tục xử lý:
 *   1. Lấy thông tin người dùng từ UserService.
 *   2. In thông tin hoặc xử lý ngoại lệ nếu không tìm thấy.
 */
void AuthController::getProfile(const int userId) {
  try {
    auto userJson = services::UserService::findUserById(userId);
    if (!userJson.has_value())
      throw exceptions::NotFoundException("Người dùng không tồn tại!");

    std::string fullName = userJson.value()["fullName"];
    std::string email = userJson.value()["email"];
    std::string username = userJson.value()["username"];
    int id = userJson.value()["id"];
    bool isAdmin = userJson.value().contains("isAdmin") && userJson.value()["isAdmin"].get<bool>();
    std::string role = isAdmin ? "📗 Quản trị viên" : "👤 Khách hàng";

    // Lấy số dư ví
    double walletBalance = 0.0;
    auto walletOpt = services::WalletService::getWalletByUserId(userId);
    if (walletOpt.has_value()) {
      walletBalance = walletOpt->getPoint();
    }

    // Hiển thị thông tin
    displayUserInfo(fullName, email, username, id, role, walletBalance);
    
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

/**
 * @brief Cập nhật thông tin cá nhân của người dùng.
 *
 * Input:
 *   - userId: ID người dùng.
 *   - newFullName: Họ và tên mới.
 *   - newEmail: Email mới.
 *
 * Output: Không trả về giá trị, in thông báo kết quả.
 *
 * Thủ tục xử lý:
 *   1. Gọi AuthService để cập nhật thông tin.
 *   2. In thông báo thành công hoặc xử lý ngoại lệ.
 */
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

/**
 * @brief Admin cập nhật thông tin người dùng.
 *
 * Input:
 *   - userId: ID người dùng.
 *   - newFullName: Họ và tên mới.
 *   - newEmail: Email mới.
 *
 * Output: Không trả về giá trị, in thông báo kết quả.
 *
 * Thủ tục xử lý:
 *   1. Gọi AuthService để chỉnh sửa thông tin.
 *   2. In thông báo hoặc xử lý ngoại lệ.
 */
void AuthController::editUserInfoByAdmin(const int userId,
                                         const std::string& newFullName,
                                         const std::string& newEmail) {
  try {
    services::AuthService::editUserInfo(userId, newFullName, newEmail);
    utils::MessageHandler::logSuccess(
        "Cập nhật thông tin người dùng thành công!");
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
};

/**
 * @brief Đổi mật khẩu với xác thực OTP.
 *
 * Input:
 *   - userId: ID người dùng.
 *   - currentPassword: Mật khẩu hiện tại.
 *   - newPassword: Mật khẩu mới.
 *
 * Output: Không trả về giá trị, in thông báo kết quả.
 *
 * Thủ tục xử lý:
 *   1. Lấy email người dùng từ UserService.
 *   2. Gửi OTP và yêu cầu nhập mã OTP.
 *   3. Xác minh OTP.
 *   4. Cập nhật mật khẩu mới.
 *   5. In thông báo thành công hoặc xử lý ngoại lệ.
 */
void AuthController::changePasswordWithOTP(const int userId,
                                           const std::string& currentPassword,
                                           const std::string& newPassword) {
  try {
    auto userJson = services::UserService::findUserById(userId);
    if (!userJson.has_value())
      throw exceptions::NotFoundException("Người dùng không tồn tại!");

    std::string email = userJson->at("email").get<std::string>();
    std::string storedHash = userJson->at("passwordHash").get<std::string>();
    // Kiểm tra mật khẩu cũ
    if (!utils::hash::validatePassword(currentPassword, storedHash)) {
      throw exceptions::ValidationException("Mật khẩu hiện tại không đúng!");
    }
    
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