#include "services/WalletService.hpp"

#include "models/Wallet.hpp"
#include "utils/MessageHandler.hpp"
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace services {

bool WalletService::createWallet(int userId, double initialBalance) {
  try {
    // Kiểm tra xem user đã có ví chưa
    if (getWalletByUserId(userId)) {
      utils::MessageHandler::logWarning("User đã có ví!");
      return false;
    }

    // Tạo ví mới
    models::Wallet newWallet(userId, initialBalance);

    // Lưu thông tin ví
    json wallets = utils::storage::readJsonFile("data/wallets.json");

    json walletData;
    walletData["id"] = newWallet.getId();
    walletData["userId"] = newWallet.getUserId();
    walletData["point"] = newWallet.getPoint();
    walletData["createdAt"] = newWallet.getCreatedAt();

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

}  // namespace services