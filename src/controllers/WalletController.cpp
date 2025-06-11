#include "controllers/WalletController.hpp"

#include <iostream>

#include "models/Wallet.hpp"
#include "utils/Storage.hpp"

namespace controllers {

bool WalletController::createWallet(int userId, double initialBalance) {
  try {
    // Đọc file wallets.json hiện tại
    json wallets = utils::storage::readJsonFile("data/wallets.json");

    // Kiểm tra user đã có ví chưa
    for (const auto& wallet : wallets) {
      if (wallet["userId"] == userId) {
        std::cout << "User đã có ví!" << std::endl;
        return false;
      }
    }

    // Tạo đối tượng Wallet mới
    models::Wallet newWallet(userId, initialBalance);

    // Thêm thông tin ví mới
    json walletData;
    walletData["id"] = utils::storage::getNextWalletId(wallets);
    walletData["userId"] = newWallet.getUserId();
    walletData["balance"] = newWallet.getBalance();
    walletData["walletType"] = static_cast<int>(newWallet.getWalletType());
    walletData["createdAt"] = newWallet.getCreatedAt();
    walletData["lastUpdated"] = newWallet.getLastUpdated();

    wallets.push_back(walletData);

    // Lưu ví vào file
    if (!utils::storage::writeJsonFile("data/wallets.json", wallets)) {
      std::cout << "Không thể lưu thông tin ví!" << std::endl;
      return false;
    }

    // std::cout << "Tạo ví thành công cho user ID: " << userId << std::endl;
    return true;
  } catch (const std::exception& e) {
    std::cout << "Lỗi khi tạo ví: " << e.what() << std::endl;
    return false;
  }
}

bool WalletController::getWalletByUserId(int userId, int& walletId,
                                         double& balance) {
  try {
    json wallets = utils::storage::readJsonFile("data/wallets.json");

    for (const auto& wallet : wallets) {
      if (wallet["userId"] == userId) {
        walletId = wallet["id"];
        balance = wallet["balance"];
        return true;
      }
    }

    return false;  // Không tìm thấy ví
  } catch (const std::exception& e) {
    std::cout << "Lỗi khi tìm ví: " << e.what() << std::endl;
    return false;
  }
}

bool WalletController::getSystemWallet(int& walletId, double& balance) {
  try {
    json wallets = utils::storage::readJsonFile("data/wallets.json");

    for (const auto& wallet : wallets) {
      // walletType: 1 là SYSTEM, 0 là USER
      if (wallet["walletType"] == 1) {
        walletId = wallet["id"];
        balance = wallet["balance"];
        return true;
      }
    }

    return false;  // Không tìm thấy ví hệ thống
  } catch (const std::exception& e) {
    std::cout << "Lỗi khi tìm ví hệ thống: " << e.what() << std::endl;
    return false;
  }
}

}  // namespace controllers