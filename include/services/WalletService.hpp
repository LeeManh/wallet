#ifndef WALLET_SERVICE_HPP
#define WALLET_SERVICE_HPP

#include <string>
#include <vector>

#include "models/Wallet.hpp"

namespace services {

class WalletService {
 public:
  // Tạo ví mới cho user
  bool createWallet(int userId, double initialBalance);

  // Lấy ví của user
  models::Wallet getWalletByUserId(int userId);

  // Lấy thông tin ví hệ thống (SYSTEM wallet)
  models::Wallet getSystemWallet();

  // Lấy danh sách tất cả ví
  std::vector<models::Wallet> getAllWallets();
};

}  // namespace services

#endif