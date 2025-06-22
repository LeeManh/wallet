#pragma once

#include <string>

namespace models {

enum class WalletType {
  USER,
  SYSTEM,
};

class Wallet {
 private:
  int id;
  int userId;
  double point;
  WalletType walletType;

 public:
  // Constructor
  Wallet(int id, int userId, double point = 0.0,
         WalletType walletType = WalletType::USER);

  // Getters
  int getId() const;
  int getUserId() const;
  double getPoint() const;
  WalletType getWalletType() const;

  // Setters
  void setPoint(double newPoint);
  void setId(int newId);
  void setLastUpdated(time_t time);
};

}  // namespace models
