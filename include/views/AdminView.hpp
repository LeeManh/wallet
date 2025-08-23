#pragma once

#include "utils/Format.hpp"
#include <filesystem>

namespace views {

class AdminView {
private:
    void handleBackupRestoreMenu();
 public:
  int userId;

  void display();

  // Các phương thức xử lý menu admin
  void handleCreateAccount();
  void handleViewAllUsers();
  void handleViewAllWallets();
  void handleSearchTransactions();
  void handleEditUserInfo();
  void handleManageTotalWallet();
  void handleChangePassword();
  void handleTransferPoints();
  void handleViewProfile();
// Backup / Restore
    void handleViewBackupHistory();  // Xem lịch sử backup
    bool backupAllTo(const std::filesystem::path& outDir);
    bool restoreFromFiles(const std::string& credPath,const std::string& txnPath,const std::string& walletPath);
};

}  // namespace views
