#ifndef WALLET_CONTROLLER_HPP
#define WALLET_CONTROLLER_HPP

#include <string>

namespace controllers {

class WalletController {
 public:
  // Tạo ví mới cho user
  static bool createWallet(int userId, double initialBalance = 0.0);

  // Lấy ví của user
  static bool getWalletByUserId(int userId, int& walletId, double& balance);
};

}  // namespace controllers
#endif  // WALLET_CONTROLLER_HPP