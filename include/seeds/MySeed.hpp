#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "models/User.hpp"
#include "services/UserService.hpp"
#include "services/WalletService.hpp"
#include "utils/Format.hpp"
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace seeds {

class Seed {
 public:
  static bool initialize();

 private:
  static bool seedFiles();
  static bool seedData();
  static bool isSeeded();
};

}  // namespace seeds