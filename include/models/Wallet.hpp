#pragma once

#include <string>

#include "enums/Enums.hpp"

namespace models {

/**
 * @class Wallet
 * @brief Đại diện cho ví của người dùng hoặc hệ thống.
 *
 * Lớp này lưu thông tin về ID ví, ID người dùng sở hữu,
 * số điểm (point) hiện có, và loại ví (user/system).
 */
class Wallet {
 private:
  int id;                          // ID duy nhất của ví (primary key)
  int userId;                      // ID của người dùng sở hữu ví
  double point;                    // Số điểm hiện tại trong ví
  enums::WalletType walletType;    // Loại ví (USER, SYSTEM, ...)

 public:
  
  /**
   * @brief Constructor khởi tạo đối tượng Wallet.
   * @param id ID của ví.
   * @param userId ID người dùng sở hữu ví.
   * @param point Số điểm ban đầu trong ví (mặc định = 0.0).
   * @param walletType Loại ví (mặc định = enums::WalletType::USER).
   */
  Wallet(int id, int userId, double point = 0.0,
         enums::WalletType walletType = enums::WalletType::USER);

  /**
   * @brief Lấy ID ví.
   * @return ID của ví.
   */
  int getId() const;

  /**
   * @brief Lấy ID người dùng sở hữu ví.
   * @return ID của người dùng.
   */
  int getUserId() const;

  /**
   * @brief Lấy số điểm hiện có trong ví.
   * @return Số điểm.
   */
  double getPoint() const;

  /**
   * @brief Lấy loại ví.
   * @return Loại ví (USER, SYSTEM, ...).
   */
  enums::WalletType getWalletType() const;
};

}  // namespace models
