#include "models/Wallet.hpp"

#include <ctime>

namespace models {

// Constructor
Wallet::Wallet(int id, int userId, double point, WalletType walletType)
    : id(id), userId(userId), point(point), walletType(walletType) {}

// Getters
int Wallet::getId() const { return id; }
int Wallet::getUserId() const { return userId; }
double Wallet::getPoint() const { return point; }
WalletType Wallet::getWalletType() const { return walletType; }

// Setters
void Wallet::setPoint(double newPoint) { point = newPoint; }

void Wallet::setId(int newId) { id = newId; }

}  // namespace models