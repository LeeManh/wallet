#pragma once

#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include "enums/Enums.hpp"
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace services {

// Bộ lọc truy vấn
struct TxQuery {
  // "all" | "incoming" | "outgoing"
  std::string direction = "all";
  // lọc theo trạng thái (để trống = bỏ qua)
  std::optional<enums::TransactionStatus> status;
  // lọc theo khoảng số tiền
  std::optional<double> minAmount;
  std::optional<double> maxAmount;
  // sắp xếp: "id_asc" | "id_desc"
  std::string sort = "id_desc";
  // phân trang
  int page = 1;
  int pageSize = 20;
};

// Chỉ phụ trách TRUY VẤN lịch sử từ data/transactions.json
class TransactionHistory {
 public:
  explicit TransactionHistory(std::string dataFile = "data/transactions.json");

  // Danh sách toàn bộ giao dịch của 1 ví (mặc định sắp xếp id_desc)
  std::vector<json> listByWallet(int walletId) const;

  // Truy vấn nâng cao theo bộ lọc
  std::vector<json> queryByWallet(int walletId, const TxQuery& q) const;

 private:
  std::string dataFile_;

  // Helpers
  json readAll() const;
  static bool passDirection(int walletId, const json& tx, const std::string& dir);
};

}  // namespace services
