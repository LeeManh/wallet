#include "controllers/WalletController.hpp"

namespace controllers {

bool WalletController::createWallet(int userId, double initialBalance) {
  return walletService.createWallet(userId, initialBalance);
}

models::Wallet WalletController::getWalletByUserId(int userId) {
  return walletService.getWalletByUserId(userId);
}

models::Wallet WalletController::getSystemWallet() {
  return walletService.getSystemWallet();
}

std::vector<models::Wallet> WalletController::getAllWallets() {
  return walletService.getAllWallets();
}

}  // namespace controllers