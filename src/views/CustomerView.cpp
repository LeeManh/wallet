#include "views/CustomerView.hpp"
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "services/TransactionHistory.hpp"  
#include "controllers/AuthController.hpp"
#include "controllers/TransactionController.hpp"
#include "controllers/WalletController.hpp"
#include "utils/Format.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"
#include "utils/Utf8Console.hpp"
#include "utils/Validation.hpp"

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
 * @brief Hiển thị lịch sử giao dịch của ví người dùng (Customer).
 *
 * Input:
 *  - Wallet ID do người dùng nhập từ bàn phím.
 *    + Chỉ được phép nhập số dương.
 *    + Hệ thống kiểm tra ví có thuộc quyền sở hữu của user hiện tại hay không.
 *
 * Output:
 *  - Hiển thị bảng lịch sử giao dịch của ví đó với các cột:
 *      [STT]  [Biến động +/-Số điểm]  [Mô tả (người chuyển/nhận)].
 *  - Hiển thị thêm số dư hiện tại của ví.
 *  - Nếu không có giao dịch hoặc Wallet ID không hợp lệ → báo lỗi/thông báo.
 *
 * Thủ tục xử lý:
 *  1. Hiển thị tiêu đề "LỊCH SỬ GIAO DỊCH".
 *  2. Yêu cầu người dùng nhập Wallet ID.
 *  3. Kiểm tra:
 *      - Nếu ID không hợp lệ → báo lỗi và dừng.
 *      - Nếu ví không thuộc về user hiện tại → báo lỗi và dừng.
 *  4. Tạo truy vấn (TxQuery) để lấy danh sách giao dịch của ví.
 *  5. Sắp xếp các giao dịch theo ID giảm dần.
 *  6. Nếu không có giao dịch → thông báo và dừng.
 *  7. Nếu có:
 *      - In bảng với header (STT | Biến động | Mô tả).
 *      - Duyệt từng giao dịch:
 *          + Xác định ví là người gửi hay nhận.
 *          + Tính biến động số điểm (+/-).
 *          + Tạo mô tả ("Nhận điểm từ X" hoặc "Chuyển điểm đến Y").
 *          + In ra một dòng của bảng.
 *  8. In footer và gọi hàm lấy số dư hiện tại của ví.
 *  9. Tạm dừng, chờ người dùng nhấn phím tiếp tục.
 */

void CustomerView::handleViewTransactionHistory() {
  utils::MessageHandler::logMessage("+-------------------------------------------------------------+");
  utils::MessageHandler::logMessage("|                  LỊCH SỬ GIAO DỊCH                          |");
  utils::MessageHandler::logMessage("+-------------------------------------------------------------+");

  std::string widStr = utils::input::getInput("Nhập Wallet ID: ");
  if (!utils::validation::isPositiveNumber(widStr)) {
    utils::MessageHandler::logError("Wallet ID không hợp lệ!");
    utils::input::pauseInput();
    return;
  }

  int walletId = std::stoi(widStr);
  if (!controllers::WalletController::isWalletOwnedByUser(userId, walletId)) {
    utils::MessageHandler::logError("Bạn chỉ xem được lịch sử giao dịch ví của mình");
    utils::input::pauseInput();
    return;
  }

  services::TxQuery q; q.direction = "all"; q.sort = "id_desc";
  services::TransactionHistory history;
  auto rows = history.queryByWallet(walletId, q);

  std::sort(rows.begin(), rows.end(),
            [](const auto& a, const auto& b){ return a.value("id",0) > b.value("id",0); });

  if (rows.empty()) {
    utils::MessageHandler::logMessage("Không có giao dịch nào.");
    utils::input::pauseInput();
    return;
  }

  // ===== cấu hình cột =====
  constexpr int W_STT  = 3;
  constexpr int W_MOVE = 12;
  constexpr int W_DESC = 40;

  auto hline = [&](){
    return std::string("+")
      + std::string(W_STT+2, '-') + "+"
      + std::string(W_MOVE+2,'-') + "+"
      + std::string(W_DESC+2,'-') + "+";
  };

  // Cache tên user theo walletId
  std::unordered_map<int,std::string> nameCache;
  auto fullNameOfWallet = [&](int wid)->const std::string&{
    auto it = nameCache.find(wid);
    if (it != nameCache.end()) return it->second;
    auto ownerIdOpt = controllers::WalletController::getOwnerIdByWalletId(wid);
    std::string name = "Unknown";
    if (ownerIdOpt) {
      if (auto u = services::UserService::findUserById(*ownerIdOpt))
        name = u->value("fullName", "user#" + std::to_string(*ownerIdOpt));
      else
        name = "user#" + std::to_string(*ownerIdOpt);
    } else name = "W#" + std::to_string(wid);
    return nameCache.emplace(wid, std::move(name)).first->second;
  };

  // ===== header =====
  utils::MessageHandler::logMessage(hline());
  {
    std::ostringstream hdr;
    hdr << "| " << vnconsole::pad_right("STT", W_STT)
        << " | " << vnconsole::pad_right("Biến động", W_MOVE)
        << " | " << vnconsole::pad_right("Mô tả", W_DESC)
        << " |";
    utils::MessageHandler::logMessage(hdr.str());
  }
  utils::MessageHandler::logMessage(hline());

  // ===== nội dung =====
  int no = 1;
  for (const auto& tx : rows) {
    int    src = tx.value("sourceWalletId", -1);
    int    dst = tx.value("destinationWalletId", -1);
    double amt = tx.value("amount", 0.0);

    // ±amount
    std::ostringstream amtss; amtss << std::fixed << std::setprecision(2) << amt;
    bool in = (dst == walletId);
    std::string movement = (in ? "+" : "-") + amtss.str();

    // Mô tả
    const std::string& partner = in ? fullNameOfWallet(src) : fullNameOfWallet(dst);
    std::string desc = in
      ? ("Nhận điểm từ " + partner)
      : ("Chuyển điểm đến " + partner);

    // In 1 dòng
    std::ostringstream line;
    line << "| " << vnconsole::pad_left(std::to_string(no++), W_STT)
         << " | " << vnconsole::pad_left(movement, W_MOVE)
         << " | " << vnconsole::pad_right(desc, W_DESC)
         << " |";
    utils::MessageHandler::logMessage(line.str());
  }

  // ===== footer + số dư =====
  utils::MessageHandler::logMessage(hline());

  // Gọi để hiển thị số dư hiện tại
  controllers::WalletController::getWalletByUserId(userId);

  utils::input::pauseInput();
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
  std::string newPassword;
  while (true) {
    newPassword = utils::input::getInput("Nhập mật khẩu mới (≥ 6 ký tự):");
    if (!utils::validation::isValidPassword(newPassword)) {
      utils::MessageHandler::logError("Mật khẩu không hợp lệ! (tối thiểu 6 ký tự)");
      utils::input::pauseInput();
      continue; // quay lại vòng lặp, yêu cầu nhập lại
    }
    break;
  }
  std::string confirmPassword =
      utils::input::getInput("Nhập lại mật khẩu mới: ");

  if (newPassword != confirmPassword) {
    utils::MessageHandler::logError("Mật khẩu mới không khớp!");
    utils::input::pauseInput();
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
