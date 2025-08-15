#include "services/TransactionHistory.hpp"
#include <algorithm>

using services::TransactionHistory;

// Phòng khi chưa có macro (ví dụ build tool lạ)
#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

TransactionHistory::TransactionHistory(std::string dataFile)
    : dataFile_(std::move(dataFile)) {
  if (dataFile_.empty()) {
    dataFile_ = std::string(DATA_DIR) + "/transactions.json";
  }
}

json TransactionHistory::readAll() const {
  json arr = utils::storage::readJsonFile(dataFile_);
  if (!arr.is_array()) return json::array();
  return arr;
}

bool TransactionHistory::passDirection(int walletId, const json& tx, const std::string& dir) {
  int src = tx.value("sourceWalletId", -1);
  int dst = tx.value("destinationWalletId", -1);
  if (dir == "all") return (src == walletId) || (dst == walletId);
  if (dir == "outgoing") return src == walletId;
  if (dir == "incoming") return dst == walletId;
  return (src == walletId) || (dst == walletId);
}

std::vector<json> TransactionHistory::listByWallet(int walletId) const {
  json all = readAll();
  std::vector<json> out;
  out.reserve(all.size());
  for (const auto& tx : all) {
    if (!tx.is_object()) continue;
    int src = tx.value("sourceWalletId", -1);
    int dst = tx.value("destinationWalletId", -1);
    if (src == walletId || dst == walletId) out.push_back(tx);
  }
  std::sort(out.begin(), out.end(), [](const json& a, const json& b){
    return a.value("id", 0) > b.value("id", 0);
  });
  return out;
}

std::vector<json> TransactionHistory::queryByWallet(int walletId, const services::TxQuery& q) const {
  json all = readAll();
  std::vector<json> out;
  out.reserve(all.size());

  for (const auto& tx : all) {
    if (!tx.is_object()) continue;

    if (!passDirection(walletId, tx, q.direction)) continue;

    if (q.status.has_value()) {
      int st = tx.value("status", -1);
      if (st != static_cast<int>(*q.status)) continue;
    }

    double amount = tx.value("amount", 0.0);
    if (q.minAmount.has_value() && amount < *q.minAmount) continue;
    if (q.maxAmount.has_value() && amount > *q.maxAmount) continue;

    out.push_back(tx);
  }

  // sort
  if (q.sort == "id_asc") {
    std::sort(out.begin(), out.end(), [](const json& a, const json& b){
      return a.value("id", 0) < b.value("id", 0);
    });
  } else { // id_desc
    std::sort(out.begin(), out.end(), [](const json& a, const json& b){
      return a.value("id", 0) > b.value("id", 0);
    });
  }

  // paging
  int page = std::max(1, q.page);
  int ps   = std::max(1, q.pageSize);
  size_t start = static_cast<size_t>((page - 1) * ps);
  if (start >= out.size()) return {};
  size_t end = std::min(out.size(), start + static_cast<size_t>(ps));
  return std::vector<json>(out.begin() + static_cast<long>(start),
                           out.begin() + static_cast<long>(end));
}
