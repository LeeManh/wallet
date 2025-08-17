#pragma once

#include <ctime>
#include <string>

#include "enums/Enums.hpp"

namespace models {

/**
 * @brief Đại diện cho một giao dịch giữa hai ví trong hệ thống.
 *
 * Lớp Transaction lưu trữ thông tin về giao dịch như ví nguồn, ví đích,
 * số tiền, trạng thái giao dịch, và mã định danh giao dịch.
 */
class Transaction {
 private:
  int id;                           // Primary key
  int sourceWalletId  ;               // Ví nguồn
  int destinationWalletId;          // Ví đích
  double amount;                    // Số tiền giao dịch
  enums::TransactionStatus status;  // Trạng thái giao dịch

 public:

  /**
   * @brief Khởi tạo một đối tượng Transaction.
   *
   * @param id Mã định danh giao dịch.
   * @param sourceWalletId ID ví nguồn.
   * @param destinationWalletId ID ví đích.
   * @param amount Số tiền giao dịch.
   * @param status Trạng thái giao dịch (mặc định là PENDING).
   */
  Transaction(
      int id, int sourceWalletId, int destinationWalletId, double amount,
      enums::TransactionStatus status = enums::TransactionStatus::PENDING);

  /**
   * @brief Lấy mã định danh giao dịch.
   * @return ID giao dịch.
   */
  int getId() const;

  /**
   * @brief Lấy ID ví nguồn.
   * @return ID ví nguồn.
   */
  int getSourceWalletId() const;

  /**
   * @brief Lấy ID ví đích.
   * @return ID ví đích.
   */
  int getDestinationWalletId() const;

  /**
   * @brief Lấy số tiền giao dịch.
   * @return Số tiền.
   */
  double getAmount() const;

  /**
   * @brief Lấy trạng thái giao dịch.
   * @return Giá trị TransactionStatus.
   */
  enums::TransactionStatus getStatus() const;
};

}  // namespace models
