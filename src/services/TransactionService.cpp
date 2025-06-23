#include "services/TransactionService.hpp"

#include "exceptions/Exception.hpp"
#include "utils/Storage.hpp"

namespace services {

models::Transaction TransactionService::createTransaction(
    int sourceWalletId, int destinationWalletId, double amount,
    enums::TransactionStatus status) {
  json transactions = utils::storage::readJsonFile("data/transactions.json");

  // Tạo transaction data
  int transactionId = utils::storage::getNextTransactionId();

  // Tạo instance
  models::Transaction transaction(transactionId, sourceWalletId,
                                  destinationWalletId, amount, status);

  json transactionData;
  transactionData["id"] = transaction.getId();
  transactionData["sourceWalletId"] = transaction.getSourceWalletId();
  transactionData["destinationWalletId"] = transaction.getDestinationWalletId();
  transactionData["amount"] = transaction.getAmount();
  transactionData["status"] = transaction.getStatus();
  transactions.push_back(transactionData);

  if (!utils::storage::writeJsonFile("data/transactions.json", transactions))
    throw exceptions::StorageException("Không thể lưu thông tin giao dịch!");

  return transaction;
}

models::Transaction TransactionService::updateTransaction(
    int transactionId, enums::TransactionStatus status) {
  json transactions = utils::storage::readJsonFile("data/transactions.json");

  for (auto& transaction : transactions) {
    if (transaction["id"] == transactionId) {
      transaction["status"] = status;

      utils::storage::writeJsonFile("data/transactions.json", transactions);

      // Tạo Transaction object từ JSON data đã cập nhật
      return models::Transaction(transaction["id"].get<int>(),
                                 transaction["sourceWalletId"].get<int>(),
                                 transaction["destinationWalletId"].get<int>(),
                                 transaction["amount"].get<double>(),
                                 static_cast<enums::TransactionStatus>(
                                     transaction["status"].get<int>()));
    }
  }

  throw exceptions::NotFoundException("Không tìm thấy transaction");
}

}  // namespace services