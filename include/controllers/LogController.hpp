#pragma once

#include <string>
#include <vector>
#include <models/User.hpp>
#include <models/Wallet.hpp>
#include <enums/Enums.hpp>
namespace controllers {
    class LogController
    {
    public:
        static void printList(std::vector<models::User> users, std::vector<enums::UserInfo> userInfo);
        static void printList(std::vector<models::Wallet> wallets, std::vector<enums::WalletInfo> walletInfo);
        static void printList(models::User user, std::vector<enums::UserInfo> userInfo);
        static void printList(models::Wallet user, std::vector<enums::WalletInfo> walletInfo);
    };
}