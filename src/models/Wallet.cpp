#include "models/Wallet.hpp"

#include <ctime>

#include "enums/Enums.hpp"

namespace models {

// Constructor
Wallet::Wallet(int id, int userId, double point, enums::WalletType walletType)
    : id(id), userId(userId), point(point), walletType(walletType) {}

// Getters
int Wallet::getId() const { return id; }
int Wallet::getUserId() const { return userId; }
double Wallet::getPoint() const { return point; }
enums::WalletType Wallet::getWalletType() const { return walletType; }

}  // namespace models