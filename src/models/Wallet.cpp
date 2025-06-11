#include "models/Wallet.hpp"

#include <ctime>

namespace models {

// Constructor
Wallet::Wallet(int userId, double point, WalletType walletType, int id)
    : id(id), userId(userId), point(point), walletType(walletType) {
  time_t now = time(nullptr);
  createdAt = now;
  lastUpdated = now;
}

// Getters
int Wallet::getId() const { return id; }
int Wallet::getUserId() const { return userId; }
double Wallet::getPoint() const { return point; }
WalletType Wallet::getWalletType() const { return walletType; }
time_t Wallet::getCreatedAt() const { return createdAt; }
time_t Wallet::getLastUpdated() const { return lastUpdated; }

// Setters
void Wallet::setPoint(double newPoint) {
  point = newPoint;
  updateLastUpdated();
}

void Wallet::updateLastUpdated() { lastUpdated = time(nullptr); }

void Wallet::setId(int newId) { id = newId; }

void Wallet::setCreatedAt(time_t time) { createdAt = time; }

void Wallet::setLastUpdated(time_t time) { lastUpdated = time; }

}  // namespace models