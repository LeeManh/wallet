#pragma once

#include <string>

#include "enums/Enums.hpp"

namespace models {

class Wallet {
 private:
  int id;
  int userId;
  double point;
  enums::WalletType walletType;

 public:
  // Constructor
  Wallet(int id, int userId, double point = 0.0,
         enums::WalletType walletType = enums::WalletType::USER);

  // Getters
  int getId() const;
  int getUserId() const;
  double getPoint() const;
  enums::WalletType getWalletType() const;
};

}  // namespace models
