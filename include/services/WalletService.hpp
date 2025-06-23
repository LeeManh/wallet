#ifndef WALLET_SERVICE_HPP
#define WALLET_SERVICE_HPP

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>

#include "enums/Enums.hpp"
#include "models/Wallet.hpp"

using json = nlohmann::json;

namespace services {

class WalletService {
 public:
  // Tạo ví mới cho user
  static bool createWallet(
      int userId, double initialBalance,
      enums::WalletType walletType = enums::WalletType::USER);

  // Lấy ví của user
  static std::optional<models::Wallet> getWalletByUserId(int userId);

  // Lấy thông tin ví hệ thống (SYSTEM wallet)
  static std::optional<models::Wallet> getSystemWallet();

  // Lấy danh sách tất cả ví
  static std::vector<models::Wallet> getAllWallets();

  // In ra danh sách ví
  static void printListWallet();

  // Kiểm tra ví có tồn tại không
  static bool checkHasWallet(int walletId);

  // Kiểm tra số dư của ví
  static bool checkPoints(int walletId, double points);

  // Cập nhật điểm của ví
  static void updatePoint(int walletId, double points);

  // Rollback điểm của ví
  static void rollbackPoint(int walletId, double points);
};

}  // namespace services

#endif