#ifndef WALLET_CONTROLLER_HPP
#define WALLET_CONTROLLER_HPP

#include <string>
#include <vector>

#include "models/Wallet.hpp"

namespace controllers {

class WalletController {
 public:
  // Tạo ví mới cho user
  static bool createWallet(int userId, double initialPoint = 0.0);

  // Lấy ví của user
  static bool getWalletByUserId(int userId, int& walletId, double& point);

  // Lấy thông tin ví hệ thống (SYSTEM wallet)
  static bool getSystemWallet(int& walletId, double& point);

  // Lấy danh sách tất cả ví
  static std::vector<models::Wallet> getAllWallets();
};

}  // namespace controllers
#endif  // WALLET_CONTROLLER_HPP