#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include "enums/Enums.hpp"
#include "models/Transaction.hpp"

using json = nlohmann::json;

namespace services {

class TransactionService {
 public:
  static models::Transaction createTransaction(
      int sourceWalletId, int destinationWalletId, double amount,
      enums::TransactionStatus status = enums::TransactionStatus::PENDING);

  static models::Transaction updateTransaction(int transactionId,
                                               enums::TransactionStatus status);
};

}  // namespace services
