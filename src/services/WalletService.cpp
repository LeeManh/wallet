#include "services/WalletService.hpp"

#include <string>

#include "enums/Enums.hpp"
#include "exceptions/Exception.hpp"
#include "models/Wallet.hpp"
#include "utils/Format.hpp"
#include "utils/MessageHandler.hpp"
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace services {

/**
 * @brief Tạo một ví mới cho user.
 * 
 * @param userId ID của user cần tạo ví.
 * @param initialBalance Số điểm ban đầu của ví.
 * @param walletType Loại ví (USER hoặc SYSTEM).
 * @return true nếu tạo thành công.
 * @throws ValidationException nếu user đã có ví.
 */
bool WalletService::createWallet(int userId, double initialBalance,
                                 enums::WalletType walletType) {
  // Kiểm tra xem user đã có ví chưa
  if (getWalletByUserId(userId)) {
    throw exceptions::ValidationException("User đã có ví!");
  }

  json wallets = utils::storage::readJsonFile("data/wallets.json");

  // Tạo ví mới
  int newWalletId = utils::storage::getNextWalletId(wallets);
  models::Wallet newWallet(newWalletId, userId, initialBalance, walletType);

  json walletData;
  walletData["id"] = newWallet.getId();
  walletData["userId"] = newWallet.getUserId();
  walletData["point"] = newWallet.getPoint();
  walletData["walletType"] = newWallet.getWalletType();

  wallets.push_back(walletData);

  utils::storage::writeJsonFile("data/wallets.json", wallets);
  return true;
}

/**
 * @brief Lấy ví của user dựa vào userId.
 * 
 * @param userId ID của user.
 * @return Wallet nếu tồn tại, std::nullopt nếu không tìm thấy.
 */
std::optional<models::Wallet> WalletService::getWalletByUserId(int userId) {
  json wallets = utils::storage::readJsonFile("data/wallets.json");

  for (const auto& walletData : wallets) {
    if (walletData["userId"].get<int>() == userId) {
      return models::Wallet(
          walletData["id"].get<int>(), walletData["userId"].get<int>(),
          walletData["point"].get<double>(), enums::WalletType::USER);
    }
  }

  return std::nullopt;
}

/**
 * @brief Lấy ví hệ thống (SYSTEM wallet).
 * 
 * @return Wallet nếu tồn tại, std::nullopt nếu không tìm thấy.
 */
std::optional<models::Wallet> WalletService::getSystemWallet() {
  json wallets = utils::storage::readJsonFile("data/wallets.json");

  for (const auto& walletData : wallets) {
    if (walletData.contains("walletType") &&
        walletData["walletType"].get<int>() == 1) {
      return models::Wallet(
          walletData["id"].get<int>(), walletData["userId"].get<int>(),
          walletData["point"].get<double>(), enums::WalletType::SYSTEM);
    }
  }

  return std::nullopt;
}

/**
 * @brief Lấy danh sách tất cả ví trong hệ thống.
 * 
 * @return Vector chứa các Wallet.
 */
std::vector<models::Wallet> WalletService::getAllWallets() {
  json wallets = utils::storage::readJsonFile("data/wallets.json");
  std::vector<models::Wallet> result;

  for (const auto& walletData : wallets) {
    // Kiểm tra xem walletType có tồn tại không, nếu không thì mặc định là
    // USER (0)
    int walletTypeValue = 0;  // Mặc định là USER
    if (walletData.contains("walletType")) {
      walletTypeValue = walletData["walletType"].get<int>();
    }

    enums::WalletType type = (walletTypeValue == 1) ? enums::WalletType::SYSTEM
                                                    : enums::WalletType::USER;

    result.push_back(models::Wallet(walletData["id"].get<int>(),
                                    walletData["userId"].get<int>(),
                                    walletData["point"].get<double>(), type));
  }

  return result;
}

/**
 * @brief In danh sách ví ra màn hình console.
 * 
 * @note Không có giá trị trả về.
 */
void WalletService::printListWallet() {
  auto wallets = getAllWallets();

  if (wallets.empty()) {
    utils::MessageHandler::logWarning("Không có ví nào trong hệ thống!");
  } else {
    utils::MessageHandler::logMessage("");

    int count = 1;
    for (const auto& wallet : wallets) {
      std::string walletTypeStr =
          (wallet.getWalletType() == enums::WalletType::SYSTEM) ? "SYSTEM"
                                                                : "USER";

      utils::MessageHandler::logMessage(
          "[" + std::to_string(count) +
          "] Ví ID: " + std::to_string(wallet.getId()) +
          " | User: " + std::to_string(wallet.getUserId()) +
          " | Số điểm: " + utils::format::formatPoint(wallet.getPoint()) +
          " điểm" + " | Loại: " + walletTypeStr);
      count++;
    }

    utils::MessageHandler::logMessage(std::string(60, '-'));
    utils::MessageHandler::logMessage("Tổng số ví: " +
                                      std::to_string(wallets.size()));

    double totalPoint = 0;
    int userWallets = 0;
    int systemWallets = 0;

    for (const auto& wallet : wallets) {
      totalPoint += wallet.getPoint();
      if (wallet.getWalletType() == enums::WalletType::SYSTEM) {
        systemWallets++;
      } else {
        userWallets++;
      }
    }

    utils::MessageHandler::logMessage(
        "Tổng số điểm hệ thống: " + utils::format::formatPoint(totalPoint) +
        " điểm");
    utils::MessageHandler::logMessage(
        "Ví người dùng: " + std::to_string(userWallets) +
        " | Ví hệ thống: " + std::to_string(systemWallets));
  }
}

/**
 * @brief Kiểm tra ví có tồn tại không dựa vào walletId.
 * 
 * @param walletId ID của ví.
 * @return true nếu tồn tại, false nếu không.
 */
bool WalletService::checkHasWallet(int walletId) {
  json wallets = utils::storage::readJsonFile("data/wallets.json");
  for (const auto& wallet : wallets) {
    if (wallet["id"] == walletId) return true;
  }

  return false;
}

/**
 * @brief Kiểm tra ví có đủ điểm để giao dịch hay không.
 * 
 * @param walletId ID của ví.
 * @param points Số điểm cần kiểm tra.
 * @return true nếu đủ, false nếu không.
 */
bool WalletService::checkPoints(int walletId, double points) {
  json wallets = utils::storage::readJsonFile("data/wallets.json");

  for (const auto& wallet : wallets) {
    if (wallet["id"] == walletId && wallet["point"] >= points) return true;
  }

  return false;
}

/**
 * @brief Cập nhật số điểm của ví bằng cách cộng thêm.
 * 
 * @param walletId ID của ví.
 * @param points Số điểm cộng thêm (có thể âm để trừ).
 * @throws NotFoundException nếu không tìm thấy ví.
 */
void WalletService::updatePoint(int walletId, double points) {
  json wallets = utils::storage::readJsonFile("data/wallets.json");

  for (auto& wallet : wallets) {
    if (wallet["id"] == walletId) {
      double walletPoint = wallet["point"];
      wallet["point"] = walletPoint + points;

      utils::storage::writeJsonFile("data/wallets.json", wallets);
      return;
    }
  }

  // Only throw if wallet not found
  throw exceptions::NotFoundException("Không tìm thấy ví " +
                                      std::to_string(walletId));
}

/**
 * @brief Hoàn tác số điểm của ví về một giá trị cụ thể.
 * 
 * @param walletId ID của ví.
 * @param points Giá trị điểm cần khôi phục.
 * @throws NotFoundException nếu không tìm thấy ví.
 */
void WalletService::rollbackPoint(int walletId, double points) {
  json wallets = utils::storage::readJsonFile("data/wallets.json");

  for (auto& wallet : wallets) {
    if (wallet["id"] == walletId) {
      wallet["point"] = points;

      utils::storage::writeJsonFile("data/wallets.json", wallets);
      return;
    }
  }

  throw exceptions::NotFoundException("Không tìm thấy ví " +
                                      std::to_string(walletId));
}
}  // namespace services