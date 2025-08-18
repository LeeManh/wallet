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

void WalletController::printListWallet() {
  try {
    services::WalletService::printListWallet();
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}
bool WalletController::isWalletOwnedByUser(int userId, int walletId) {
  try {
    // Trường hợp hệ thống mỗi user chỉ có 1 ví:
    if (auto w = services::WalletService::getWalletByUserId(userId)) {
      // Ưu tiên dùng getter theo model của bạn; nếu model là getWalletId() thì đổi lại cho khớp
      return w->getId() == walletId; 
    }

    // Phòng khi hệ thống có nhiều ví / API khác: quét danh sách để chắc chắn
    for (const auto& w : services::WalletService::getAllWallets()) {
      // Nếu model là getUserId()/getId() khác tên, đổi lại cho đúng project của bạn
      if (w.getUserId() == userId && w.getId() == walletId) {
        return true;
      }
    }
    return false;
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return false;
  }
}
//Gọi user qua wallet ID
std::optional<int> WalletController::getOwnerIdByWalletId(int walletId) {
  try {
    for (const auto& w : services::WalletService::getAllWallets()) {
      // Đổi getId/getUserId theo đúng getter của model bạn nếu khác tên
      if (w.getId() == walletId) {
        return w.getUserId();
      }
    }
    return std::nullopt;
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return std::nullopt;
  }
}

std::string WalletController::getOwnerNameByWalletId(int walletId) {
  try {
    auto ownerId = getOwnerIdByWalletId(walletId);
    if (!ownerId) return "W#" + std::to_string(walletId);   // không tìm thấy ví
    // Chưa có UserService -> hiển thị theo userId
    return "user#" + std::to_string(*ownerId);
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return "W#" + std::to_string(walletId);
  }
}
}  // namespace controllers
