#include "models/Transaction.hpp"

#include <ctime>

#include "enums/Enums.hpp"

namespace models {

// Constructor
Transaction::Transaction(int id, int sourceWalletId, int destinationWalletId,
                         double amount, enums::TransactionStatus status)
    : id(id),
      sourceWalletId(sourceWalletId),
      destinationWalletId(destinationWalletId),
      amount(amount),
      status(status) {}

// Getters
int Transaction::getId() const { return id; }
int Transaction::getSourceWalletId() const { return sourceWalletId; }
int Transaction::getDestinationWalletId() const { return destinationWalletId; }
double Transaction::getAmount() const { return amount; }
enums::TransactionStatus Transaction::getStatus() const { return status; }

}  // namespace models