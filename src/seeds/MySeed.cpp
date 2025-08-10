#include "seeds/MySeed.hpp"

#include <nlohmann/json.hpp>

#include "enums/Enums.hpp"
#include "exceptions/Exception.hpp"
#include "models/User.hpp"
#include "services/UserService.hpp"
#include "services/WalletService.hpp"
#include "utils/ExceptionHandler.hpp"
#include "utils/Format.hpp"
#include "utils/Storage.hpp"
#include "controllers/LogController.hpp"

using json = nlohmann::json;
namespace seeds {
bool isUser = false;
bool isAdmin = false;

/**
 * @brief Khởi tạo dữ liệu ban đầu của hệ thống (seed).
 *
 * Input: Không có.
 * Output: 
 *   - true nếu khởi tạo thành công hoặc dữ liệu đã tồn tại.
 *   - false nếu xảy ra lỗi.
 *
 * Thủ tục xử lý:
 *   1. Kiểm tra nếu dữ liệu đã được seed trước đó → trả về true.
 *   2. Gọi seedFiles() để tạo thư mục và file dữ liệu trống.
 *   3. Gọi seedData() để thêm dữ liệu mặc định (admin và user mẫu).
 *   4. Hiển thị dữ liệu vừa được khởi tạo bằng printSeededData().
 *   5. Ghi log thành công hoặc bắt lỗi và xử lý.
 */
bool Seed::initialize() {
  try {
    if (isSeeded()) return true;

    seedFiles();

    seedData();
    printSeededData(isUser, isAdmin);
    utils::MessageHandler::logSuccess("Khởi tạo dữ liệu thành công!");
    return true;
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return false;
  }
}

/**
 * @brief Hiển thị danh sách người dùng đã được seed vào hệ thống.
 *
 * Input:
 *   - isAdmin: true nếu hiển thị tài khoản admin.
 *   - isUser: true nếu hiển thị tài khoản user.
 *
 * Output: Không trả về giá trị, in danh sách ra màn hình.
 *
 * Thủ tục xử lý:
 *   1. In tiêu đề “KHỞI TẠO DỮ LIỆU”.
 *   2. Lấy danh sách user từ UserService tùy theo isAdmin/isUser.
 *   3. Gọi LogController để in danh sách user.
 */
void Seed::printSeededData(const bool isAdmin, const bool isUser) {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│                KHỞI TẠO DỮ LIỆU             │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");
  std::vector<models::User> users;
  try {
    if (isAdmin) {
      auto aUsers = services::UserService::getAllUsers(true);
      users.insert(users.end(), aUsers.begin(), aUsers.end());
    } 
    if (isUser) {
      auto uUsers = services::UserService::getAllUsers(false);
      users.insert(users.end(), uUsers.begin(), uUsers.end());
    }
    std::vector<enums::UserInfo> userInfo = {
        enums::UserInfo::ID, enums::UserInfo::USERNAME,
        enums::UserInfo::FULL_NAME, enums::UserInfo::EMAIL};
    controllers::LogController::printListUsers(users, userInfo);
  } catch (const std::exception& e) {
    throw e;
  }

}

/**
 * @brief Tạo thư mục và các file dữ liệu JSON trống để lưu thông tin hệ thống.
 *
 * Input: Không có.
 * Output: true nếu tạo thành công, ném exception nếu lỗi.
 *
 * Thủ tục xử lý:
 *   1. Đảm bảo thư mục "data" tồn tại.
 *   2. Tạo các file users.json, wallets.json, transactions.json, otps.json
 *      với dữ liệu mặc định là mảng rỗng.
 */
bool Seed::seedFiles() {
  try {
    // Tạo thư mục data nếu chưa tồn tại
    utils::storage::ensureDirectoryExists("data");

    // Tạo các file JSON với dữ liệu mặc định
    json emptyArray = json::array();

    utils::storage::createFile("data/users.json", emptyArray);
    utils::storage::createFile("data/wallets.json", emptyArray);
    utils::storage::createFile("data/transactions.json", emptyArray);
    utils::storage::createFile("data/otps.json", emptyArray);

    return true;

  } catch (const std::exception& e) {
    throw e;
  }
}

/**
 * @brief Thêm dữ liệu mặc định vào hệ thống.
 *
 * Input: Không có.
 * Output: true nếu thêm thành công, ném exception nếu lỗi.
 *
 * Thủ tục xử lý:
 *   1. Tạo tài khoản admin với mật khẩu mặc định và gán isAdmin = true.
 *   2. Tạo ví hệ thống cho admin với số dư 1000.
 *   3. Tạo danh sách user mẫu, thêm vào hệ thống và gán isUser = true.
 *   4. Mỗi user được tạo ví với số dư khởi tạo 50.
 */
bool Seed::seedData() {
  try {
    // Tạo admin user
    models::User admin = services::UserService::createUser(
        "admin", "123456", "admin@wallet.com", "Administrator", true);
    isAdmin = true;
    // Tạo ví hệ thống (chính là ví của admin)
    services::WalletService::createWallet(admin.getId(), 1000.0,
                                          enums::WalletType::SYSTEM);

    // Tạo một số user mẫu
    std::vector<std::tuple<std::string, std::string, std::string, std::string>>
        sampleUsers = {
            {"user1", "123456", "user1@example.com", "Nguyễn Văn A"}};
    isUser = true;
    for (const auto& [username, password, email, fullName] : sampleUsers) {
      models::User user = services::UserService::createUser(username, password,
                                                            email, fullName);

      // Tạo ví cho user với 50 điểm khởi tạo
      double initialBalance = 50.0;
      services::WalletService::createWallet(user.getId(), initialBalance,
                                            enums::WalletType::USER);
    }

    return true;

  } catch (const std::exception& e) {
    throw e;
  }
}

/**
 * @brief Kiểm tra dữ liệu đã được seed hay chưa.
 *
 * Input: Không có.
 * Output:
 *   - true nếu đã tồn tại dữ liệu admin.
 *   - false nếu chưa seed hoặc có lỗi khi đọc file.
 *
 * Thủ tục xử lý:
 *   1. Kiểm tra file data/users.json có tồn tại không.
 *   2. Đọc dữ liệu và tìm user có username = "admin".
 *   3. Nếu tìm thấy → trả về true, ngược lại trả về false.
 */
bool Seed::isSeeded() {
  try {
    // Kiểm tra xem file có tồn tại không
    if (!utils::storage::fileExists("data/users.json")) {
      return false;
    }

    // Kiểm tra xem đã có admin user chưa
    json users = utils::storage::readJsonFile("data/users.json");
    for (const auto& user : users) {
      if (user["username"] == "admin") {
        return true;
      }
    }
    return false;
  } catch (const std::exception& e) {
    // Nếu có lỗi khi đọc file, coi như chưa seeded
    return false;
  }
}

}  // namespace seeds