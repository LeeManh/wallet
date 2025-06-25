#pragma once

#include <ctime>
#include <string>

#include "enums/Enums.hpp"

namespace models {

class Transaction {
 private:
  int id;                           // Primary key
  int sourceWalletId;               // Ví nguồn
  int destinationWalletId;          // Ví đích
  double amount;                    // Số tiền giao dịch
  enums::TransactionStatus status;  // Trạng thái giao dịch

 public:
  // Constructor
  Transaction(
      int id, int sourceWalletId, int destinationWalletId, double amount,
      enums::TransactionStatus status = enums::TransactionStatus::PENDING);

  // Getters
  int getId() const;
  int getSourceWalletId() const;
  int getDestinationWalletId() const;
  double getAmount() const;
  enums::TransactionStatus getStatus() const;
};

}  // namespace models
