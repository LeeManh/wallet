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

using json = nlohmann::json;

namespace seeds {

bool Seed::initialize() {
  try {
    if (isSeeded()) return true;

    seedFiles();

    seedData();

    utils::MessageHandler::logSuccess("Khởi tạo dữ liệu thành công!");
    return true;
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return false;
  }
}

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

bool Seed::seedData() {
  try {
    // Tạo admin user
    models::User admin = services::UserService::createUser(
        "admin", "123456", "admin@wallet.com", "Administrator", true);

    // Tạo ví hệ thống (chính là ví của admin)
    services::WalletService::createWallet(admin.getId(), 1000.0,
                                          enums::WalletType::SYSTEM);

    // Tạo một số user mẫu
    std::vector<std::tuple<std::string, std::string, std::string, std::string>>
        sampleUsers = {
            {"user1", "123456", "user1@example.com", "Nguyễn Văn A"}};

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