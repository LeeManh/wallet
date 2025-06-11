#include "models/Wallet.hpp"

#include <ctime>

namespace models {

// Constructor
Wallet::Wallet(int userId, double balance, WalletType walletType, int id)
    : id(id), userId(userId), balance(balance), walletType(walletType) {
  time_t now = time(nullptr);
  createdAt = now;
  lastUpdated = now;
}

// Getters
int Wallet::getId() const { return id; }
int Wallet::getUserId() const { return userId; }
double Wallet::getBalance() const { return balance; }
WalletType Wallet::getWalletType() const { return walletType; }
time_t Wallet::getCreatedAt() const { return createdAt; }
time_t Wallet::getLastUpdated() const { return lastUpdated; }

// Setters
void Wallet::setBalance(double newBalance) {
  balance = newBalance;
  updateLastUpdated();
}

void Wallet::updateLastUpdated() { lastUpdated = time(nullptr); }

void Wallet::setId(int newId) { id = newId; }

void Wallet::setCreatedAt(time_t time) { createdAt = time; }

void Wallet::setLastUpdated(time_t time) { lastUpdated = time; }

}  // namespace models