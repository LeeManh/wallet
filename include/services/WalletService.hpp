#ifndef WALLET_SERVICE_HPP
#define WALLET_SERVICE_HPP

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>

#include "models/Wallet.hpp"

using json = nlohmann::json;

namespace services {

class WalletService {
 public:
  // Tạo ví mới cho user
  static bool createWallet(
      int userId, double initialBalance,
      models::WalletType walletType = models::WalletType::USER);

  // Lấy ví của user
  static std::optional<models::Wallet> getWalletByUserId(int userId);

  // Lấy thông tin ví hệ thống (SYSTEM wallet)
  static std::optional<models::Wallet> getSystemWallet();

  // Lấy danh sách tất cả ví
  static std::vector<models::Wallet> getAllWallets();

  // In ra danh sách ví
  static void printListWallet();
};

}  // namespace services

#endif