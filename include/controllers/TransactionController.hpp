#pragma once

namespace controllers {

class TransactionController {
 public:
  static void transferPoints(int fromUserId, int toUserId, double points);
};

}  // namespace controllers