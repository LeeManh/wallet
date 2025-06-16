#ifndef WALLET_CONTROLLER_HPP
#define WALLET_CONTROLLER_HPP

#include <optional>
#include <string>
#include <vector>

#include "models/Wallet.hpp"
#include "services/WalletService.hpp"

namespace controllers {

class WalletController {
 public:
  // Tạo ví mới cho user
  static bool createWallet(int userId, double initialBalance);

  // Lấy ví của user
  static std::optional<models::Wallet> getWalletByUserId(int userId);

  // Lấy thông tin ví hệ thống (SYSTEM wallet)
  static std::optional<models::Wallet> getSystemWallet();

  // Lấy danh sách tất cả ví
  static std::vector<models::Wallet> getAllWallets();
};

}  // namespace controllers

#endif