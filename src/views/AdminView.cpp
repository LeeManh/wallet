#include "views/AdminView.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "controllers/AuthController.hpp"
#include "controllers/LogController.hpp"
#include "controllers/TransactionController.hpp"
#include "controllers/WalletController.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"

namespace views {

/**
 * @brief Hiển thị menu quản trị viên và xử lý lựa chọn chức năng.
 *
 * Hàm này liên tục hiển thị menu các chức năng dành cho quản trị viên,
 * nhận lựa chọn từ người dùng (input), sau đó gọi hàm xử lý tương ứng.
 *
 * Input: Không có tham số truyền vào, nhận lựa chọn từ bàn phím (0-9).
 * Output: Không trả về giá trị, thực hiện các chức năng quản trị viên hoặc
 * thoát khỏi menu.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị menu các chức năng quản trị viên.
 *   2. Nhận lựa chọn từ người dùng (0-9).
 *   3. Gọi hàm xử lý tương ứng với từng lựa chọn:
 *      - 1: Xem danh sách người dùng
 *      - 2: Xem danh sách ví
 *      - 3: Xem lịch sử giao dịch
 *      - 4: Tạo tài khoản mới cho người dùng
 *      - 5: Điều chỉnh thông tin người dùng
 *      - 6: Xem số dư ví tổng
 *      - 7: Đổi mật khẩu
 *      - 8: Chuyển điểm
 *      - 9: Xem thông tin cá nhân
 *      - 0: Đăng xuất (thoát khỏi vòng lặp)
 *   4. Lặp lại cho đến khi chọn 0 (đăng xuất).
 */
void AdminView::display() {
  while (true) {
    // Hiển thị menu quản trị viên
    utils::MessageHandler::logMessage(
        "┌─────────────────────────────────────────────┐");
    utils::MessageHandler::logMessage(
        "│              MENU QUẢN TRỊ VIÊN             │");
    utils::MessageHandler::logMessage(
        "├─────────────────────────────────────────────┤");
    utils::MessageHandler::logMessage(
        "│ [1] Xem danh sách người dùng                │");
    utils::MessageHandler::logMessage(
        "│ [2] Xem danh sách ví                        │");
    utils::MessageHandler::logMessage(
        "│ [3] Xem lịch sử giao dịch                   │");
    utils::MessageHandler::logMessage(
        "│ [4] Tạo tài khoản mới cho người dùng        │");
    utils::MessageHandler::logMessage(
        "│ [5] Điều chỉnh thông tin người dùng         │");
    utils::MessageHandler::logMessage(
        "│ [6] Xem số dư ví tổng                       │");
    utils::MessageHandler::logMessage(
        "│ [7] Đổi mật khẩu                            │");
    utils::MessageHandler::logMessage(
        "│ [8] Chuyển điểm                             │");
    utils::MessageHandler::logMessage(
        "│ [9] Xem thông tin cá nhân                   │");
    utils::MessageHandler::logMessage(
        "│ [0] Đăng xuất                               │");
    utils::MessageHandler::logMessage(
        "└─────────────────────────────────────────────┘");

    // Nhận lựa chọn từ người dùng (0-9)
    int choice = utils::input::getChoice(0, 9);

    // Xử lý lựa chọn
    switch (choice) {
      case 1:
        handleViewAllUsers();  // Xem danh sách người dùng
        break;
      case 2:
        handleViewAllWallets();  // Xem danh sách ví
        break;
      case 3:
        handleViewTransactionHistory();  // Xem lịch sử giao dịch
        break;
      case 4:
        handleCreateAccount();  // Tạo tài khoản mới
        break;
      case 5:
        handleEditUserInfo();  // Điều chỉnh thông tin người dùng
        break;
      case 6:
        handleManageTotalWallet();  // Xem số dư ví tổng
        break;
      case 7:
        handleChangePassword();  // Đổi mật khẩu
        break;
      case 8:
        handleTransferPoints();  // Chuyển điểm
        break;
      case 9:
        handleViewProfile();  // Xem thông tin cá nhân
        break;
      case 0:
        return;  // Đăng xuất
    }
  }
}

/**
 * @brief Tạo tài khoản mới cho người dùng (dành cho quản trị viên).
 *
 * Input: Nhập từ bàn phím tên đăng nhập, email, họ tên đầy đủ.
 * Output: Không trả về giá trị. Thông báo thành công/thất bại qua
 * MessageHandler.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị tiêu đề chức năng.
 *   2. Nhập thông tin tài khoản mới (username, email, fullName).
 *   3. Gọi controller để tạo tài khoản và sinh mật khẩu.
 */
void AdminView::handleCreateAccount() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│         TẠO TÀI KHOẢN MỚI CHO NGƯỜI DÙNG    │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  std::string username = utils::input::getInput("Nhập tên đăng nhập: ");
  std::string email = utils::input::getInput("Nhập email: ");
  std::string fullName = utils::input::getInput("Nhập họ tên đầy đủ: ");

  std::string generatedPassword;

  controllers::AuthController::registerUserByAdmin(username, email, fullName,
                                                   generatedPassword);
}

/**
 * @brief Hiển thị danh sách tất cả người dùng trong hệ thống.
 *
 * Input: Không có (dữ liệu lấy từ service).
 * Output: Hiển thị danh sách người dùng ra màn hình.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị tiêu đề.
 *   2. Lấy danh sách người dùng từ service.
 *   3. Gọi controller để in danh sách.
 *   4. Tạm dừng chờ người dùng nhấn phím tiếp tục.
 */
void AdminView::handleViewAllUsers() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│         DANH SÁCH TẤT CẢ NGƯỜI DÙNG         │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");
  auto users = services::UserService::getAllUsers();
  std::vector<enums::UserInfo> userInfo = {
      enums::UserInfo::ID, enums::UserInfo::USERNAME,
      enums::UserInfo::FULL_NAME, enums::UserInfo::EMAIL};
  controllers::LogController::printListUsers(users, userInfo);

  utils::input::pauseInput();
}

/**
 * @brief Hiển thị danh sách tất cả ví trong hệ thống.
 *
 * Input: Không có (dữ liệu lấy từ controller).
 * Output: Hiển thị danh sách ví ra màn hình.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị tiêu đề.
 *   2. Gọi controller để in danh sách ví.
 *   3. Tạm dừng chờ người dùng nhấn phím tiếp tục.
 */
void AdminView::handleViewAllWallets() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│      DANH SÁCH TẤT CẢ VÍ TRONG HỆ THỐNG     │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  controllers::WalletController::printListWallet();

  utils::input::pauseInput();
}

/**
 * @brief Hiển thị lịch sử giao dịch (đang phát triển).
 *
 * Input/Output: Hiện tại chỉ thông báo chức năng đang phát triển.
 */
void AdminView::handleViewTransactionHistory() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

/**
 * @brief Điều chỉnh thông tin người dùng (dành cho quản trị viên).
 *
 * Hàm này cho phép quản trị viên nhập ID người dùng cần chỉnh sửa,
 * sau đó nhập họ tên mới và/hoặc email mới (có thể bỏ trống nếu không đổi).
 * Nếu thông tin nhập hợp lệ, gọi controller để cập nhật thông tin người dùng.
 *
 * Input:
 *   - Nhập từ bàn phím:
 *     + ID người dùng cần chỉnh sửa (phải là số dương)
 *     + Họ tên mới (có thể bỏ trống)
 *     + Email mới (có thể bỏ trống)
 * Output:
 *   - Không trả về giá trị. Thông báo thành công/thất bại qua MessageHandler.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị tiêu đề chức năng.
 *   2. Nhập ID người dùng cần chỉnh sửa, kiểm tra hợp lệ.
 *   3. Nhập họ tên mới và email mới (có thể bỏ trống).
 *   4. Nếu cả hai trường đều bỏ trống, thông báo không có gì thay đổi.
 *   5. Nếu có thông tin mới, gọi controller để cập nhật.
 *   6. Tạm dừng chờ người dùng nhấn phím tiếp tục.
 */
void AdminView::handleEditUserInfo() {
  // Hiển thị tiêu đề chức năng
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│         ĐIỀU CHỈNH THÔNG TIN NGƯỜI DÙNG     │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  // Nhập ID người dùng cần chỉnh sửa
  std::string userIdStr =
      utils::input::getInput("Nhập ID người dùng cần chỉnh sửa: ");
  if (!utils::validation::isPositiveNumber(userIdStr)) {
    utils::MessageHandler::logError("ID người dùng không hợp lệ!");
    return;
  }
  int userId = std::stoi(userIdStr);

  // Nhập họ tên mới và email mới (có thể bỏ trống)
  std::string newFullName =
      utils::input::getInput("Nhập họ tên mới (bỏ trống nếu không đổi): ");
  std::string newEmail =
      utils::input::getInput("Nhập email mới (bỏ trống nếu không đổi): ");

  if (newFullName.empty() && newEmail.empty()) {
    utils::MessageHandler::logMessage("Không có thông tin nào được thay đổi.");
    return;
  }

  controllers::AuthController::editUserInfoByAdmin(userId, newFullName,
                                                   newEmail);

  utils::input::pauseInput();
}

/**
 * @brief Hiển thị số dư ví hệ thống.
 *
 * Input: Không có (dữ liệu lấy từ controller).
 * Output: Hiển thị số dư ví hệ thống ra màn hình.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị tiêu đề.
 *   2. Gọi controller để lấy và in số dư ví hệ thống.
 *   3. Tạm dừng chờ người dùng nhấn phím tiếp tục.
 */
void AdminView::handleManageTotalWallet() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│              XEM SỐ DƯ VÍ HỆ THỐNG          │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  controllers::WalletController::getSystemWallet();

  utils::input::pauseInput();
}

/**
 * @brief Đổi mật khẩu cho tài khoản quản trị viên.
 *
 * Input: Nhập mật khẩu hiện tại, mật khẩu mới, xác nhận mật khẩu mới từ bàn
 * phím. Output: Thông báo thành công/thất bại qua MessageHandler.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị tiêu đề chức năng.
 *   2. Nhập mật khẩu hiện tại, mật khẩu mới, xác nhận mật khẩu mới.
 *   3. Kiểm tra xác nhận mật khẩu mới.
 *   4. Nếu hợp lệ, gọi controller để đổi mật khẩu (có xác thực OTP).
 *   5. Tạm dừng chờ người dùng nhấn phím tiếp tục.
 */
void AdminView::handleChangePassword() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│                 ĐỔI MẬT KHẨU                │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  std::string currentPassword =
      utils::input::getInput("Nhập mật khẩu hiện tại: ");
  std::string newPassword = utils::input::getInput("Nhập mật khẩu mới: ");
  std::string confirmPassword =
      utils::input::getInput("Nhập lại mật khẩu mới: ");

  if (newPassword != confirmPassword) {
    utils::MessageHandler::logError("Mật khẩu mới không khớp!");
    return;
  }

  controllers::AuthController::changePasswordWithOTP(userId, currentPassword,
                                                     newPassword);

  utils::input::pauseInput();
}

/**
 * @brief Chuyển điểm từ tài khoản quản trị viên sang tài khoản người dùng khác.
 *
 * Input: Nhập ID người nhận và số điểm cần chuyển từ bàn phím.
 * Output: Thông báo thành công/thất bại qua MessageHandler.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị tiêu đề chức năng.
 *   2. Nhập ID người nhận và số điểm cần chuyển, kiểm tra hợp lệ.
 *   3. Gọi controller để thực hiện chuyển điểm.
 */
void AdminView::handleTransferPoints() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│                CHUYỂN ĐIỂM                  │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  std::string toUserId = utils::input::getInput("Nhập id người nhận nhận: ");
  if (!utils::validation::isPositiveNumber(toUserId)) {
    utils::MessageHandler::logError("ID người nhận không hợp lệ!");
    return;
  }

  std::string points = utils::input::getInput("Nhập số điểm cần chuyển: ");
  if (!utils::validation::isPositiveNumber(points)) {
    utils::MessageHandler::logError("Số điểm không hợp lệ!");
    return;
  }

  controllers::TransactionController::transferPoints(
      userId, std::stoi(toUserId), std::stod(points));
}

/**
 * @brief Hiển thị thông tin cá nhân của quản trị viên.
 *
 * Input: Không có (dữ liệu lấy từ controller).
 * Output: Hiển thị thông tin cá nhân ra màn hình.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị tiêu đề.
 *   2. Gọi controller để lấy và in thông tin cá nhân.
 *   3. Tạm dừng chờ người dùng nhấn phím tiếp tục.
 */
void AdminView::handleViewProfile() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│           THÔNG TIN CÁ NHÂN CỦA BẠN         │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  controllers::AuthController::getProfile(userId);

  utils::input::pauseInput();
}

}  // namespace views