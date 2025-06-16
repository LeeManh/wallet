#include "controllers/WalletController.hpp"

namespace controllers {

bool WalletController::createWallet(int userId, double initialBalance) {
  return walletService.createWallet(userId, initialBalance);
}

std::optional<models::Wallet> WalletController::getWalletByUserId(int userId) {
  return walletService.getWalletByUserId(userId);
}

std::optional<models::Wallet> WalletController::getSystemWallet() {
  return walletService.getSystemWallet();
}

std::vector<models::Wallet> WalletController::getAllWallets() {
  return walletService.getAllWallets();
}

}  // namespace controllers