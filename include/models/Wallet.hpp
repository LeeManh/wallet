#ifndef WALLET_HPP
#define WALLET_HPP

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
  double balance;
  WalletType walletType;
  time_t createdAt;
  time_t lastUpdated;

 public:
  // Constructor
  Wallet(int userId, double balance = 0.0,
         WalletType walletType = WalletType::USER, int id = -1);

  // Getters
  int getId() const;
  int getUserId() const;
  double getBalance() const;
  WalletType getWalletType() const;
  time_t getCreatedAt() const;
  time_t getLastUpdated() const;

  // Setters
  void setBalance(double newBalance);
  void updateLastUpdated();
};

}  // namespace models

#endif
