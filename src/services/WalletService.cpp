#include "services/WalletService.hpp"

#include "models/Wallet.hpp"
#include "utils/Format.hpp"
#include "utils/MessageHandler.hpp"
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace services {

bool WalletService::createWallet(int userId, double initialBalance,
                                 models::WalletType walletType) {
  try {
    // Kiểm tra xem user đã có ví chưa
    if (getWalletByUserId(userId)) {
      utils::MessageHandler::logWarning("User đã có ví!");
      return false;
    }

    json wallets = utils::storage::readJsonFile("data/wallets.json");

    // Tạo ví mới
    int newWalletId = utils::storage::getNextWalletId(wallets);
    models::Wallet newWallet(newWalletId, userId, initialBalance, walletType);

    json walletData;
    walletData["id"] = newWallet.getId();
    walletData["userId"] = newWallet.getUserId();
    walletData["point"] = newWallet.getPoint();
    walletData["createdAt"] = newWallet.getCreatedAt();
    walletData["walletType"] = newWallet.getWalletType();

    wallets.push_back(walletData);

    if (!utils::storage::writeJsonFile("data/wallets.json", wallets)) {
      utils::MessageHandler::logError("Không thể lưu thông tin ví!");
      return false;
    }

    return true;
  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi tạo ví", e);
    return false;
  }
}

std::optional<models::Wallet> WalletService::getWalletByUserId(int userId) {
  try {
    json wallets = utils::storage::readJsonFile("data/wallets.json");

    for (const auto& walletData : wallets) {
      if (walletData["userId"].get<int>() == userId) {
        return models::Wallet(
            walletData["id"].get<int>(), walletData["userId"].get<int>(),
            walletData["point"].get<double>(), models::WalletType::USER);
      }
    }

    return std::nullopt;
  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi tìm ví", e);
    return std::nullopt;
  }
}

std::optional<models::Wallet> WalletService::getSystemWallet() {
  try {
    json wallets = utils::storage::readJsonFile("data/wallets.json");

    for (const auto& walletData : wallets) {
      if (walletData.contains("walletType") &&
          walletData["walletType"].get<int>() == 1) {
        return models::Wallet(
            walletData["id"].get<int>(), walletData["userId"].get<int>(),
            walletData["point"].get<double>(), models::WalletType::SYSTEM);
      }
    }

    return std::nullopt;
  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi tìm ví hệ thống", e);
    return std::nullopt;
  }
}

std::vector<models::Wallet> WalletService::getAllWallets() {
  try {
    json wallets = utils::storage::readJsonFile("data/wallets.json");
    std::vector<models::Wallet> result;

    for (const auto& walletData : wallets) {
      // Kiểm tra xem walletType có tồn tại không, nếu không thì mặc định là
      // USER (0)
      int walletTypeValue = 0;  // Mặc định là USER
      if (walletData.contains("walletType")) {
        walletTypeValue = walletData["walletType"].get<int>();
      }

      models::WalletType type = (walletTypeValue == 1)
                                    ? models::WalletType::SYSTEM
                                    : models::WalletType::USER;

      result.push_back(models::Wallet(walletData["id"].get<int>(),
                                      walletData["userId"].get<int>(),
                                      walletData["point"].get<double>(), type));
    }

    return result;
  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi đọc danh sách ví", e);
    return std::vector<models::Wallet>();
  }
}

void WalletService::printListWallet() {
  auto wallets = getAllWallets();

  if (wallets.empty()) {
    utils::MessageHandler::logWarning("Không có ví nào trong hệ thống!");
  } else {
    utils::MessageHandler::logMessage("");

    int count = 1;
    for (const auto& wallet : wallets) {
      char createdStr[20];
      struct tm* timeinfo;

      time_t createdAt = wallet.getCreatedAt();
      timeinfo = localtime(&createdAt);
      strftime(createdStr, sizeof(createdStr), "%d/%m/%Y %H:%M", timeinfo);

      std::string walletTypeStr =
          (wallet.getWalletType() == models::WalletType::SYSTEM) ? "SYSTEM"
                                                                 : "USER";

      utils::MessageHandler::logMessage(
          "[" + std::to_string(count) +
          "] Ví ID: " + std::to_string(wallet.getId()) +
          " | User: " + std::to_string(wallet.getUserId()) + " | Số điểm: " +
          utils::format::formatPoint(wallet.getPoint()) + " điểm" +
          " | Loại: " + walletTypeStr + " | Tạo: " + std::string(createdStr));
      count++;
    }

    utils::MessageHandler::logMessage(std::string(60, '-'));
    utils::MessageHandler::logMessage("Tổng số ví: " +
                                      std::to_string(wallets.size()));

    double totalPoint = 0;
    int userWallets = 0;
    int systemWallets = 0;

    for (const auto& wallet : wallets) {
      totalPoint += wallet.getPoint();
      if (wallet.getWalletType() == models::WalletType::SYSTEM) {
        systemWallets++;
      } else {
        userWallets++;
      }
    }

    utils::MessageHandler::logMessage(
        "Tổng số điểm hệ thống: " + utils::format::formatPoint(totalPoint) +
        " điểm");
    utils::MessageHandler::logMessage(
        "Ví người dùng: " + std::to_string(userWallets) +
        " | Ví hệ thống: " + std::to_string(systemWallets));
  }
}

}  // namespace services