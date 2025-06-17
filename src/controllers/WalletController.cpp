#include "controllers/WalletController.hpp"

#include "utils/Format.hpp"
#include "utils/MessageHandler.hpp"

namespace controllers {

bool WalletController::createWallet(int userId, double initialBalance) {
  return services::WalletService::createWallet(userId, initialBalance);
}

void WalletController::getWalletByUserId(int userId) {
  try {
    auto wallet = services::WalletService::getWalletByUserId(userId);
    if (!wallet) {
      utils::MessageHandler::logError("Không tìm thấy ví của bạn");
    } else {
      utils::MessageHandler::logMessage(
          "Số dư điểm hiện tại của bạn: " +
          utils::format::formatPoint(wallet.value().getPoint()) + " điểm");
    }

  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Không thể lấy thông tin số dư!");
  }
}

void WalletController::getSystemWallet() {
  auto systemWallet = services::WalletService::getSystemWallet();

  if (systemWallet) {
    utils::MessageHandler::logMessage(
        "Số dư ví hệ thống hiện tại: " +
        utils::format::formatPoint(systemWallet.value().getPoint()) + " điểm");
  } else {
    utils::MessageHandler::logError(
        "Không tìm thấy ví hệ thống hoặc có lỗi xảy ra!");
    utils::MessageHandler::logMessage(
        "Vui lòng kiểm tra lại cấu hình hệ thống.");
  }
}

std::vector<models::Wallet> WalletController::getAllWallets() {
  return services::WalletService::getAllWallets();
}

void WalletController::printListWallet() {
  services::WalletService::printListWallet();
}

}  // namespace controllers