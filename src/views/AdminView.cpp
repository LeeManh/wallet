#include "views/AdminView.hpp"
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include "services/TransactionHistory.hpp"  
#include "controllers/AuthController.hpp"
#include "controllers/LogController.hpp"
#include "controllers/TransactionController.hpp"
#include "controllers/WalletController.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"
#include "services/TransactionBackup.hpp"
#include "services/CredentialBackup.hpp"
#include "services/WalletBackup.hpp"
#include "services/BackupHistory.hpp"
#include "services/UserService.hpp"
#include "utils/Utf8Console.hpp"

using utils::MessageHandler;
namespace fs = std::filesystem;
// Hàm tạo timestamp
static std::string nowTimestamp() {
    auto t = std::time(nullptr);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y%m%d_%H%M%S");
    return oss.str();
   }
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
 *      - 10: Sao lưu / Phục hồi giao dịch
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
        "│ [10] Sao lưu / Phục hồi dữ liệu             │");
    utils::MessageHandler::logMessage(
        "│ [0] Đăng xuất                               │");
    utils::MessageHandler::logMessage(
        "└─────────────────────────────────────────────┘");

    // Nhận lựa chọn từ người dùng (0-10)
    int choice = utils::input::getChoice(0, 10);

    // Xử lý lựa chọn
    switch (choice) {
      case 1:
        handleViewAllUsers();  // Xem danh sách người dùng
        break;
      case 2:
        handleViewAllWallets();  // Xem danh sách ví
        break;
      case 3:
        handleSearchTransactions();// Xem lịch sử giao dịch
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
      case 10:
        handleBackupRestoreMenu();
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
      "│            DANH SÁCH TẤT CẢ VÍ              │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  controllers::WalletController::printListWallet();

  utils::input::pauseInput();
}

/**
 * @brief Tra cứu lịch sử giao dịch (dành cho ADMIN).
 *
 * Input:
 *  - Wallet ID do admin nhập từ bàn phím.
 *    + Nếu nhập "all" → hiển thị toàn bộ giao dịch của tất cả ví.
 *    + Nếu nhập số hợp lệ → hiển thị giao dịch liên quan đến ví đó.
 *
 * Output:
 *  - Hiển thị bảng lịch sử giao dịch ra màn hình.
 *  - Nếu là 1 ví cụ thể → hiển thị thêm số dư hiện tại của ví đó.
 *
 * Thủ tục xử lý:
 *  1. Hiển thị tiêu đề "TRA CỨU LỊCH SỬ GIAO DỊCH (ADMIN)".
 *  2. Yêu cầu admin nhập Wallet ID hoặc "all".
 *  3. Nếu "all":
 *      - Lấy danh sách tất cả các ví.
 *      - Truy vấn và gộp toàn bộ giao dịch (loại bỏ liệt kê duuplicate do 1 giao dịch sẽ được ghi nhận 2 lần: 1 chuyển điểm và 1 nhận điểm).
 *      - Sắp xếp giảm dần theo ID và hiển thị bảng (STT, Từ người dùng, Đến người dùng, Số điểm).
 *  4. Nếu nhập Wallet ID cụ thể:
 *      - Kiểm tra hợp lệ.
 *      - Truy vấn giao dịch của ví đó, sắp xếp giảm dần theo ID.
 *      - Hiển thị bảng (STT, Từ người dùng, Đến người dùng, Số điểm).
 *      - Lấy thêm số dư hiện tại của ví từ WalletController và in ra màn hình.
 *  5. Nếu không có giao dịch nào → thông báo và dừng.
 *  6. Tạm dừng chờ người dùng nhấn phím tiếp tục.
 */
void AdminView::handleSearchTransactions() {
  utils::MessageHandler::logMessage("┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage("│      TRA CỨU LỊCH SỬ GIAO DỊCH (ADMIN)      │");
  utils::MessageHandler::logMessage("└─────────────────────────────────────────────┘");

  std::string key = utils::input::getInput("Nhập Wallet ID (gõ 'all' để xem tất cả): ");

  services::TxQuery query;
  query.direction = "all";
  query.sort      = "id_desc";
  services::TransactionHistory history;

  // Cache tên user theo walletId
  std::unordered_map<int, std::string> nameCache;
  auto fullNameOfWallet = [&](int wid) -> const std::string& {
    auto it = nameCache.find(wid);
    if (it != nameCache.end()) return it->second;

    std::string name = "Unknown";
    if (auto ownerId = controllers::WalletController::getOwnerIdByWalletId(wid)) {
      if (auto u = services::UserService::findUserById(*ownerId)) {
        name = u->value("fullName", "user#" + std::to_string(*ownerId));
      } else {
        name = "user#" + std::to_string(*ownerId);
      }
    } else {
      name = "W#" + std::to_string(wid);
    }
    return nameCache.emplace(wid, std::move(name)).first->second;
  };

  // ===== cấu hình bảng + helpers in header/footer =====
  constexpr int W_STT  = 3;
  constexpr int W_FROM = 20;
  constexpr int W_TO   = 20;
  constexpr int W_AMT  = 12;

  auto make_hline = [=]() {
    return std::string("+")
      + std::string(static_cast<std::size_t>(W_STT  + 2), '-') + "+"
      + std::string(static_cast<std::size_t>(W_FROM + 2), '-') + "+"
      + std::string(static_cast<std::size_t>(W_TO   + 2), '-') + "+"
      + std::string(static_cast<std::size_t>(W_AMT  + 2), '-') + "+";
  };

  auto printHeader = [&]() {
    utils::MessageHandler::logMessage(make_hline());
    std::ostringstream hdr;
    hdr << "| " << vnconsole::pad_right("STT",            W_STT)
        << " | " << vnconsole::pad_right("Từ người dùng",  W_FROM)
        << " | " << vnconsole::pad_right("Đến người dùng", W_TO)
        << " | " << vnconsole::pad_right("Số điểm",        W_AMT)
        << " |";
    utils::MessageHandler::logMessage(hdr.str());
    utils::MessageHandler::logMessage(make_hline());
  };

  auto printFooter = [&]() { utils::MessageHandler::logMessage(make_hline()); };

  // ================== CHẾ ĐỘ ALL (khử trùng theo id) ==================
  if (key == "all" || key == "ALL" || key == "All") {
    auto wallets = controllers::WalletController::getAllWallets();

    struct Row { int id; int src; int dst; double amt; };
    std::vector<Row> rowsAll;
    std::unordered_set<int> seenIds;

    for (const auto& w : wallets) {
      int wid = w.getId();                         // đổi getter nếu khác tên
      auto rows = history.queryByWallet(wid, query);
      for (const auto& tx : rows) {
        int id = tx.value("id", 0);
        if (id > 0 && !seenIds.insert(id).second)  // khử trùng khi đã gặp id
          continue;
        rowsAll.push_back(Row{
          id,
          tx.value("sourceWalletId", -1),
          tx.value("destinationWalletId", -1),
          tx.value("amount", 0.0)
        });
      }
    }

    std::sort(rowsAll.begin(), rowsAll.end(),
              [](const Row& a, const Row& b){ return a.id > b.id; });

    if (rowsAll.empty()) {
      utils::MessageHandler::logMessage("Không có giao dịch nào.");
      utils::input::pauseInput();
      return;
    }

    printHeader();
    int no = 1;
    for (const auto& r : rowsAll) {
      std::ostringstream amtss; amtss << std::fixed << std::setprecision(2) << r.amt;
      std::ostringstream line;
      line << "| " << vnconsole::pad_left(std::to_string(no++), W_STT)
           << " | " << vnconsole::pad_right(fullNameOfWallet(r.src), W_FROM)
           << " | " << vnconsole::pad_right(fullNameOfWallet(r.dst), W_TO)
           << " | " << vnconsole::pad_left(amtss.str(), W_AMT)
           << " |";
      utils::MessageHandler::logMessage(line.str());
    }
    printFooter();
    utils::input::pauseInput();
    return;
  }

  // ================== CHẾ ĐỘ 1 VÍ ==================
  if (!utils::validation::isPositiveNumber(key)) {
    utils::MessageHandler::logError("Wallet ID không hợp lệ!");
    utils::input::pauseInput();
    return;
  }
  int walletId = std::stoi(key);

  auto rows = history.queryByWallet(walletId, query);
  std::sort(rows.begin(), rows.end(),
            [](const auto& a, const auto& b){ return a.value("id",0) > b.value("id",0); });

  if (rows.empty()) {
    utils::MessageHandler::logMessage("Không có giao dịch nào.");
    utils::input::pauseInput();
    return;
  }

  printHeader();

  int stt = 1;
  for (const auto& tx : rows) {
    int    src = tx.value("sourceWalletId", -1);
    int    dst = tx.value("destinationWalletId", -1);
    double amt = tx.value("amount", 0.0);

    std::ostringstream amtss; amtss << std::fixed << std::setprecision(2) << amt;

    std::ostringstream line;
    line << "| " << vnconsole::pad_left(std::to_string(stt++), W_STT)
         << " | " << vnconsole::pad_right(fullNameOfWallet(src), W_FROM)
         << " | " << vnconsole::pad_right(fullNameOfWallet(dst), W_TO)
         << " | " << vnconsole::pad_left(amtss.str(), W_AMT)
         << " |";
    utils::MessageHandler::logMessage(line.str());
  }

  printFooter();

  // Lấy SỐ DƯ HIỆN TẠI từ service
  double currentBalance = 0.0;
  bool found = false;
  for (const auto& w : controllers::WalletController::getAllWallets()) {
    if (w.getId() == walletId) {           // đổi getter cho khớp model nếu cần
      currentBalance = w.getPoint();       // getter point hiện có
      found = true;
      break;
    }
  }
  if (!found) {
    utils::MessageHandler::logError("Không tìm thấy ví!");
  } else {
    std::ostringstream balanceLine;
    balanceLine << "Số dư hiện tại của ví [Wallet ID: "
                << walletId <<"]: "
                << std::fixed << std::setprecision(2) << currentBalance;
    utils::MessageHandler::logMessage(balanceLine.str());
  }

  utils::input::pauseInput();
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
/**
 * Backup & Restore dữ liệu hệ thống
 * ---------------------------------
 * Hai hàm này chịu trách nhiệm sao lưu và phục hồi toàn bộ dữ liệu chính:
 *  - credentials.json  : thông tin người dùng
 *  - transactions.json : lịch sử giao dịch
 *  - wallets.json      : trạng thái số dư ví
 *
 * Input:
 *  - backupAllTo(outDir):
 *      + outDir: đường dẫn thư mục đích để tạo bản sao lưu.
 *  - restoreFromFiles(credPath, txnPath, walletPath):
 *      + credPath   : đường dẫn tới file credentials.json (có thể rỗng).
 *      + txnPath    : đường dẫn tới file transactions.json (có thể rỗng).
 *      + walletPath : đường dẫn tới file wallets.json (có thể rỗng).
 *
 * Output:
 *  - Trả về true nếu toàn bộ thao tác thành công.
 *  - Trả về false nếu có lỗi hoặc thiếu file cần thiết.
 *
 * Cách thực thi:
 *  - backupAllTo:
 *      1. Kiểm tra và tạo thư mục outDir nếu chưa tồn tại.
 *      2. Xuất dữ liệu từ CredentialBackup, TransactionBackup, WalletBackup ra file JSON.
 *      3. Ghi lại lịch sử vào BackupHistory.
 *      4. Trả kết quả cho người dùng.
 *
 *  - restoreFromFiles:
 *      1. Kiểm tra tham số đầu vào, nếu rỗng hết thì báo lỗi.
 *      2. Với từng file (credentials, transactions, wallets):
 *         - Nếu tồn tại: gọi service import.
 *         - Nếu không tồn tại: báo lỗi và đánh dấu fail.
 *      3. Nếu tất cả file cần thiết import thành công thì báo "Phục hồi thành công".
 *         Ngược lại báo "Phục hồi thất bại".
 */
bool views::AdminView::backupAllTo(const std::filesystem::path& outDir) {
    try {
        if (!fs::exists(outDir))
            fs::create_directories(outDir);

        std::string credFile   = (outDir / "credentials.json").string();
        std::string txnFile    = (outDir / "transactions.json").string();
        std::string walletFile = (outDir / "wallets.json").string();

        services::CredentialBackup::exportToFile(credFile);
        services::TransactionBackup::exportToFile(txnFile);
        services::WalletBackup::exportToFile(walletFile);

        services::BackupHistory::logBackup(nowTimestamp(), outDir.string());

        MessageHandler::logSuccess("Sao lưu thành công -> " + outDir.string());
        return true;
    } catch (const std::exception& e) {
        MessageHandler::logError(std::string("Lỗi sao lưu: ") + e.what());
    }
    return false;
}

/**
 * @brief Phục hồi dữ liệu hệ thống từ các file backup.
 *
 * Mục đích:
 *   Đọc dữ liệu từ các file sao lưu (thông tin tài khoản, giao dịch, ví)
 *   và import trở lại hệ thống.
 *
 * Input:
 *   - credPath: Đường dẫn tới file backup thông tin tài khoản (credentials).
 *   - txnPath: Đường dẫn tới file backup giao dịch (transactions).
 *   - walletPath: Đường dẫn tới file backup ví (wallet).
 *
 * Output:
 *   - true: Nếu phục hồi thành công tất cả các file hợp lệ.
 *   - false: Nếu không có file nào được nhập hoặc có ít nhất một file thất bại.
 *
 * Thủ tục xử lý:
 *   1. Kiểm tra nếu cả 3 đường dẫn đều rỗng → báo lỗi và trả về false.
 *   2. Với từng file:
 *        - Nếu đường dẫn không rỗng và file tồn tại → gọi service import.
 *        - Nếu file không tồn tại → báo lỗi và đánh dấu thất bại.
 *   3. Nếu tất cả các file hợp lệ → báo thành công, trả về true.
 *   4. Nếu có file thất bại hoặc xảy ra exception → báo lỗi, trả về false.
 *
 * Ngoại lệ:
 *   - Bắt và log std::exception nếu có lỗi trong quá trình import.
 */
bool views::AdminView::restoreFromFiles(const std::string& credPath,
                                        const std::string& txnPath,
                                        const std::string& walletPath) {
    try {
        if (credPath.empty() && txnPath.empty() && walletPath.empty()) {
            MessageHandler::logError("Chưa nhập đường dẫn nào để phục hồi.");
            return false;
        }

        bool ok1 = true, ok2 = true, ok3 = true;

        if (!credPath.empty()) {
            if (fs::exists(credPath)) {
                services::CredentialBackup::importFromFile(credPath);
            } else {
                MessageHandler::logError("Không thấy file: " + credPath);
                ok1 = false;
            }
        }

        if (!txnPath.empty()) {
            if (fs::exists(txnPath)) {
                services::TransactionBackup::importFromFile(txnPath);
            } else {
                MessageHandler::logError("Không thấy file: " + txnPath);
                ok2 = false;
            }
        }

        if (!walletPath.empty()) {
            if (fs::exists(walletPath)) {
                services::WalletBackup::importFromFile(walletPath);
            } else {
                MessageHandler::logError("Không thấy file: " + walletPath);
                ok3 = false;
            }
        }

        if (ok1 && ok2 && ok3) {
            MessageHandler::logSuccess("Phục hồi thành công.");
            return true;
        } else {
            MessageHandler::logError("Phục hồi thất bại.");
            return false;
        }

    } catch (const std::exception& e) {
        MessageHandler::logError(std::string("Lỗi phục hồi: ") + e.what());
    }
    return false;
}

/**
 * @brief Hiển thị menu sao lưu & phục hồi dữ liệu cho Admin.
 *
 * Mục đích:
 *   Cung cấp các lựa chọn để quản lý dữ liệu hệ thống:
 *   - Tạo bản sao lưu mới
 *   - Xem lịch sử sao lưu
 *   - Khôi phục từ bản sao lưu đã có
 *   - Khôi phục từ file/thư mục bên ngoài
 *
 * Input:
 *   - Người dùng chọn thao tác từ bàn phím (0–4).
 *
 * Output:
 *   - Thông báo kết quả thực hiện (thành công hoặc lỗi).
 *
 * Thủ tục xử lý:
 *   1. Hiển thị menu lựa chọn.
 *   2. Người dùng nhập số (0–4).
 *      - 0 → Quay lại.
 *      - 1 → Tạo bản sao lưu mới trong thư mục `backups/<timestamp>`.
 *      - 2 → In ra toàn bộ lịch sử sao lưu.
 *      - 3 → Liệt kê lịch sử sao lưu, cho phép chọn bản backup để khôi phục.
 *      - 4 → Nhập đường dẫn file/thư mục bên ngoài, phục hồi dữ liệu từ đó.
 *   3. Kiểm tra đường dẫn/file hợp lệ trước khi phục hồi.
 *   4. Thông báo kết quả (thành công/thất bại) ra màn hình.
 */
void views::AdminView::handleBackupRestoreMenu() {
    while (true) {
        utils::MessageHandler::logMessage(
            "\n+─────────────────────────────────────────────────+\n"
            "│           SAO LƯU & PHỤC HỒI DỮ LIỆU            │\n"
            "+─────────────────────────────────────────────────+\n"
            "│ 1. Tạo bản sao lưu mới                          │\n"
            "│ 2. Xem lịch sử sao lưu                          │\n"
            "│ 3. Khôi phục từ bản sao lưu                     │\n"
            "│ 4. Khôi phục từ dữ liệu ngoài (file/folder)     │\n"
            "│ 0. Quay lại                                     │\n"
            "+─────────────────────────────────────────────────+\n"
        );
        int choice = utils::input::getChoice(0, 4);
        if (choice == 0) break;

        if (choice == 1) {
            std::string dir = "backups/" + nowTimestamp();
            backupAllTo(dir);
        } 
        else if (choice == 2) {
            services::BackupHistory::printAll();
        } 
        else if (choice == 3) {
            auto history = services::BackupHistory::getHistory();
            if (history.empty()) {
                MessageHandler::logMessage("Chưa có bản sao lưu nào để khôi phục.");
                continue;
            }

            services::BackupHistory::printAll();
            std::string idxStr = utils::input::getInput("Chọn số thứ tự backup để khôi phục: ");
            int idx = -1;
            try {
                idx = std::stoi(idxStr) - 1;
            } catch (...) {
                MessageHandler::logError("Lựa chọn không hợp lệ.");
                continue;
            }

            if (idx < 0 || idx >= (int)history.size()) {
                MessageHandler::logError("Lựa chọn không hợp lệ.");
                continue;
            }

            auto rec = history[idx];
            std::string cred   = rec.directory + "/credentials.json";
            std::string txn    = rec.directory + "/transactions.json";
            std::string wallet = rec.directory + "/wallets.json";
            restoreFromFiles(cred, txn, wallet);
        }
        else if (choice == 4) {
            std::string path = utils::input::getInput("Nhập đường dẫn file hoặc thư mục: ");

            if (!fs::exists(path)) {
                MessageHandler::logError("Đường dẫn không tồn tại.");
                continue;
            }

            std::string credFile, txnFile, walletFile;

            if (fs::is_directory(path)) {
                credFile   = (fs::path(path) / "credentials.json").string();
                txnFile    = (fs::path(path) / "transactions.json").string();
                walletFile = (fs::path(path) / "wallets.json").string();
            } else {
                std::string fname = fs::path(path).filename().string();
                if (fname == "credentials.json") {
                    credFile = path;
                } else if (fname == "transactions.json") {
                    txnFile = path;
                } else if (fname == "wallets.json") {
                    walletFile = path;
                } else {
                    MessageHandler::logError("Chỉ chấp nhận file credentials.json, transactions.json hoặc wallets.json");
                    continue;
                }
            }
            bool ok = restoreFromFiles(
                fs::exists(credFile) ? credFile : "",
                fs::exists(txnFile) ? txnFile : "",
                fs::exists(walletFile) ? walletFile : ""
            );

            if (ok) {
                MessageHandler::logSuccess("Phục hồi dữ liệu từ copy ngoài thành công!");
            } else {
                MessageHandler::logError("Phục hồi dữ liệu từ copy ngoài thất bại!");
            }
        }
    }
}

}  // namespace views
