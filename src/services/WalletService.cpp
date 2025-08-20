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
 * @brief Lấy thông tin cụ thể từ đối tượng Wallet.
 *
 * Hàm này trả về một chuỗi chứa thông tin được yêu cầu từ đối tượng ví
 * (wallet) dựa trên kiểu thông tin được chỉ định.
 *
 * @param wallet Đối tượng `models::Wallet` chứa thông tin ví.
 * @param info Kiểu thông tin muốn lấy, được định nghĩa trong `enums::WalletInfo`.
 * Các tùy chọn bao gồm:
 * - `WALLET_ID`: ID của ví.
 * - `USER_ID`: ID của người dùng sở hữu ví.
 * - `WALLET_TYPE`: Loại ví ("SYSTEM" hoặc "USER").
 * - `POINT`: Số điểm hiện có trong ví.
 * @return Một `std::string` chứa thông tin tương ứng. Trả về chuỗi rỗng nếu
 * loại thông tin không hợp lệ.
 */
std::string WalletService::getWalletInfo(models::Wallet wallet, enums::WalletInfo info) {
  switch (info) {
    case enums::WalletInfo::WALLET_ID:
      return std::to_string(wallet.getId());
    case enums::WalletInfo::USER_ID:
      return std::to_string(wallet.getUserId());
    case enums::WalletInfo::WALLET_TYPE:
      return (wallet.getWalletType() == enums::WalletType::SYSTEM) ? "SYSTEM": "USER";
    case enums::WalletInfo::POINT:
      return std::to_string(static_cast<int>(wallet.getPoint()));
    default:
      return "";
  }
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