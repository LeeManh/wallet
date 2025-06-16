#ifndef WALLET_CONTROLLER_HPP
#define WALLET_CONTROLLER_HPP

#include <optional>
#include <string>
#include <vector>

#include "models/Wallet.hpp"
#include "services/WalletService.hpp"
namespace controllers {

class WalletController {
 private:
  services::WalletService walletService;

 public:
  // Tạo ví mới cho user
  bool createWallet(int userId, double initialBalance);

  // Lấy ví của user
  std::optional<models::Wallet> getWalletByUserId(int userId);

  // Lấy thông tin ví hệ thống (SYSTEM wallet)
  std::optional<models::Wallet> getSystemWallet();

  // Lấy danh sách tất cả ví
  std::vector<models::Wallet> getAllWallets();
};

}  // namespace controllers

#endif