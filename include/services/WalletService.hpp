#ifndef WALLET_SERVICE_HPP
#define WALLET_SERVICE_HPP

#include <optional>
#include <string>
#include <vector>

#include "models/Wallet.hpp"

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
};

}  // namespace services

#endif