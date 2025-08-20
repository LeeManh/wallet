#include "views/CustomerView.hpp"

#include "controllers/AuthController.hpp"
#include "controllers/LogController.hpp"
#include "controllers/TransactionController.hpp"
#include "controllers/WalletController.hpp"
#include "utils/Format.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"
#include "exceptions/Exception.hpp"

namespace views {

/**
 * @brief Hiển thị menu chức năng dành cho khách hàng.
 *
 * Mục đích:
 *   Cho phép khách hàng lựa chọn các chức năng như xem số dư, chuyển điểm,
 *   xem lịch sử giao dịch, chỉnh sửa thông tin cá nhân, đổi mật khẩu, xem thông tin cá nhân hoặc đăng xuất.
 *
 * Input:
 *   - Không có tham số đầu vào.
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Điều hướng tới chức năng tương ứng với lựa chọn của người dùng.
 */
void CustomerView::display() {
  while (true) {
    utils::MessageHandler::logMessage(
        "┌─────────────────────────────────────────────┐");
    utils::MessageHandler::logMessage(
        "│              MENU KHÁCH HÀNG                │");
    utils::MessageHandler::logMessage(
        "├─────────────────────────────────────────────┤");
    utils::MessageHandler::logMessage(
        "│ [1] Xem số dư                               │");
    utils::MessageHandler::logMessage(
        "│ [2] Chuyển điểm                             │");
    utils::MessageHandler::logMessage(
        "│ [3] Xem lịch sử giao dịch                   │");
    utils::MessageHandler::logMessage(
        "│ [4] Điều chỉnh thông tin cá nhân            │");
    utils::MessageHandler::logMessage(
        "│ [5] Đổi mật khẩu                            │");
    utils::MessageHandler::logMessage(
        "│ [6] Xem thông tin cá nhân                   │");
    utils::MessageHandler::logMessage(
        "│ [0] Đăng xuất                               │");
    utils::MessageHandler::logMessage(
        "└─────────────────────────────────────────────┘");

    int choice = utils::input::getChoice(0, 6);

    switch (choice) {
      case 1:
        handleViewBalance();
        break;
      case 2:
        handleTransferPoints();
        break;
      case 3:
        handleViewTransactionHistory();
        break;
      case 4:
        handleEditProfile();
        break;
      case 5:
        handleChangePassword();
        break;
      case 6:
        handleViewProfile();
        break;
      case 0:
        return;
    }
  }
}

/**
 * @brief Hiển thị số dư điểm của khách hàng hiện tại.
 *
 * Mục đích:
 *   Lấy và hiển thị thông tin ví điểm của khách hàng dựa trên userId.
 *
 * Input:
 *   - Không có tham số đầu vào (sử dụng userId nội bộ của đối tượng).
 *
 * Output:
 *   - Không trả về giá trị.
 *   - In số dư điểm ra màn hình.
 */
void CustomerView::handleViewBalance() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│              XEM SỐ DƯ ĐIỂM                 │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  controllers::WalletController::getWalletByUserId(userId);

  utils::MessageHandler::logMessage("\nNhấn Enter để tiếp tục...");
  std::cin.get();
}

/**
 * @brief Thực hiện chuyển điểm sang tài khoản người dùng khác.
 *
 * Mục đích:
 *   Cho phép khách hàng nhập ID người nhận và số điểm cần chuyển, sau đó thực hiện giao dịch.
 *
 * Input:
 *   - Không có tham số đầu vào (thông tin lấy từ bàn phím).
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Thông báo kết quả giao dịch.
 */
void CustomerView::handleTransferPoints() {
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
 * @brief Hiển thị lịch sử giao dịch của khách hàng.
 *
 * Mục đích:
 *   Cho phép khách hàng xem các giao dịch đã thực hiện.
 *
 * Input:
 *   - Không có tham số đầu vào.
 *
 * Output:
 *   - Không trả về giá trị.
 *   - In thông tin lịch sử giao dịch ra màn hình.
 */
void CustomerView::handleViewTransactionHistory() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

/**
 * @brief Cho phép khách hàng chỉnh sửa thông tin cá nhân.
 *
 * Mục đích:
 *   Cập nhật họ tên và email của khách hàng trong hệ thống.
 *
 * Input:
 *   - Không có tham số đầu vào (thông tin nhập từ bàn phím).
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Lưu thông tin mới vào hệ thống.
 */
void CustomerView::handleEditProfile() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│         ĐIỀU CHỈNH THÔNG TIN CÁ NHÂN        │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  // Lấy thông tin hiện tại
  controllers::AuthController::getProfile(userId);

  std::string newFullName = utils::input::getInput("Nhập họ tên mới (bỏ trống nếu không đổi): ");
  std::string newEmail = utils::input::getInput("Nhập email mới (bỏ trống nếu không đổi): ");

  controllers::AuthController::updateProfile(userId, newFullName, newEmail);

  utils::input::pauseInput();
}

/**
 * @brief Thay đổi mật khẩu của khách hàng.
 *
 * Mục đích:
 *   Xác thực mật khẩu hiện tại và đặt mật khẩu mới cho tài khoản.
 *
 * Input:
 *   - Không có tham số đầu vào (thông tin nhập từ bàn phím).
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Cập nhật mật khẩu mới nếu hợp lệ.
 */
void CustomerView::handleChangePassword() {
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
 * @brief Hiển thị thông tin cá nhân của khách hàng.
 *
 * Mục đích:
 *   Lấy và in thông tin hồ sơ của khách hàng.
 *
 * Input:
 *   - Không có tham số đầu vào.
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Hiển thị thông tin cá nhân ra màn hình.
 */
void CustomerView::handleViewProfile() {
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