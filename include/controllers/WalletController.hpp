#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>

#include "models/Wallet.hpp"
#include "services/WalletService.hpp"

using json = nlohmann::json;

namespace controllers {

class WalletController {
 public:
  // Tạo ví mới cho user
  static bool createWallet(int userId, double initialBalance);

  // Lấy ví của user
  static void getWalletByUserId(int userId);

  // Lấy thông tin ví hệ thống (SYSTEM wallet)
  static void getSystemWallet();

  // Lấy danh sách tất cả ví
  static std::vector<models::Wallet> getAllWallets();

  // In ra danh sách ví
  static void printListWallet();
 // kiểm tra có phải ID ví của người dùng không
  static bool isWalletOwnedByUser(int userId, int walletId);
// hàm gọi tên uesr
  static std::optional<int> getOwnerIdByWalletId(int walletId);
  static std::string        getOwnerNameByWalletId(int walletId);
};

}  // namespace controllers
