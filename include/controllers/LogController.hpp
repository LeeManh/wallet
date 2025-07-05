#pragma once

#include <string>
#include <vector>
#include <models/User.hpp>
#include <enums/Enums.hpp>

namespace controllers {
    class LogController
    {
    public:
        static void printListUsers(std::vector<models::User> users, std::vector<enums::UserInfo> userInfo);
    };
}