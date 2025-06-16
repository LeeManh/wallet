#include "controllers/WalletController.hpp"

namespace controllers {

bool WalletController::createWallet(int userId, double initialBalance) {
  return services::WalletService::createWallet(userId, initialBalance);
}

std::optional<models::Wallet> WalletController::getWalletByUserId(int userId) {
  return services::WalletService::getWalletByUserId(userId);
}

std::optional<models::Wallet> WalletController::getSystemWallet() {
  return services::WalletService::getSystemWallet();
}

std::vector<models::Wallet> WalletController::getAllWallets() {
  return services::WalletService::getAllWallets();
}

}  // namespace controllers