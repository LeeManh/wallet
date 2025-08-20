#include "controllers/WalletController.hpp"

#include "utils/ExceptionHandler.hpp"
#include "utils/Format.hpp"
#include "utils/MessageHandler.hpp"

namespace controllers {

bool WalletController::createWallet(int userId, double initialBalance) {
  try {
    return services::WalletService::createWallet(userId, initialBalance);
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return false;
  }
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
    utils::ExceptionHandler::handleException(e);
  }
}

void WalletController::getSystemWallet() {
  try {
    auto systemWallet = services::WalletService::getSystemWallet();

    if (systemWallet) {
      utils::MessageHandler::logMessage(
          "Số dư ví hệ thống hiện tại: " +
          utils::format::formatPoint(systemWallet.value().getPoint()) +
          " điểm");
    } else {
      utils::MessageHandler::logError(
          "Không tìm thấy ví hệ thống hoặc có lỗi xảy ra!");
      utils::MessageHandler::logMessage(
          "Vui lòng kiểm tra lại cấu hình hệ thống.");
    }
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

std::vector<models::Wallet> WalletController::getAllWallets() {
  try {
    return services::WalletService::getAllWallets();
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return std::vector<models::Wallet>();
  }
}

}  // namespace controllers