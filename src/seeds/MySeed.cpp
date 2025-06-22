#include "seeds/MySeed.hpp"

#include <nlohmann/json.hpp>

#include "enums/Enums.hpp"
#include "models/User.hpp"
#include "services/UserService.hpp"
#include "services/WalletService.hpp"
#include "utils/Format.hpp"
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace seeds {

bool Seed::initialize() {
  if (isSeeded()) {
    utils::MessageHandler::logMessage("Dữ liệu đã được khởi tạo!");
    return true;
  }

  if (!seedFiles()) {
    utils::MessageHandler::logError("Không thể tạo các file dữ liệu!");
    return false;
  }

  if (!seedData()) {
    utils::MessageHandler::logError("Không thể khởi tạo dữ liệu!");
    return false;
  }

  utils::MessageHandler::logSuccess("Khởi tạo dữ liệu thành công!");
  return true;
}

bool Seed::seedFiles() {
  // Tạo thư mục data nếu chưa tồn tại
  if (!utils::storage::ensureDirectoryExists("data")) {
    return false;
  }

  // Tạo các file JSON với dữ liệu mặc định
  json emptyArray = json::array();

  if (!utils::storage::createFile("data/users.json", emptyArray)) return false;
  if (!utils::storage::createFile("data/wallets.json", emptyArray))
    return false;
  if (!utils::storage::createFile("data/transactions.json", emptyArray))
    return false;
  if (!utils::storage::createFile("data/otps.json", emptyArray)) return false;

  return true;
}

bool Seed::seedData() {
  try {
    // Tạo admin user
    models::User admin = services::UserService::createUser(
        "admin", "admin123", "admin@wallet.com", "Administrator", true);

    if (!services::UserService::saveUser(admin)) {
      utils::MessageHandler::logError("Không thể lưu admin user!");
      return false;
    }

    // Tạo ví cho admin
    if (!services::WalletService::createWallet(admin.getId(), 1000.0,
                                               enums::WalletType::USER)) {
      utils::MessageHandler::logError("Không thể tạo ví cho admin!");
      return false;
    }

    // Tạo ví hệ thống
    if (!services::WalletService::createWallet(0, 0.0,
                                               enums::WalletType::SYSTEM)) {
      utils::MessageHandler::logError("Không thể tạo ví hệ thống!");
      return false;
    }

    // Tạo một số user mẫu
    std::vector<std::tuple<std::string, std::string, std::string, std::string>>
        sampleUsers = {
            {"user1", "user123", "user1@example.com", "Nguyễn Văn A"},
            {"user2", "user123", "user2@example.com", "Trần Thị B"},
            {"user3", "user123", "user3@example.com", "Lê Văn C"},
        };

    for (const auto& [username, password, email, fullName] : sampleUsers) {
      models::User user = services::UserService::createUser(username, password,
                                                            email, fullName);

      if (!services::UserService::saveUser(user)) {
        utils::MessageHandler::logError("Không thể lưu user: " + username);
        continue;
      }

      // Tạo ví cho user với số điểm ngẫu nhiên
      double initialBalance = 100.0 + (rand() % 900);  // 100-1000 điểm
      if (!services::WalletService::createWallet(user.getId(), initialBalance,
                                                 enums::WalletType::USER)) {
        utils::MessageHandler::logError("Không thể tạo ví cho user: " +
                                        username);
      }
    }

    return true;

  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi khởi tạo dữ liệu: " +
                                    std::string(e.what()));
    return false;
  }
}

bool Seed::isSeeded() {
  // Kiểm tra xem đã có admin user chưa
  json users = utils::storage::readJsonFile("data/users.json");
  for (const auto& user : users) {
    if (user["username"] == "admin") {
      return true;
    }
  }
  return false;
}

}  // namespace seeds