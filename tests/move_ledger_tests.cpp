#include <gtest/gtest.h>
#include "pinkytoe/enums.h"
#include "move_ledger.hpp"

using pinkytoe::Player;
using pinkytoe::impl::MoveLedger;

TEST(MoveLedgerTests, constructor_test) {
  MoveLedger ledger(Player::X);
  ASSERT_EQ(ledger.first_player(), Player::X);
  ASSERT_EQ(ledger.move_count(), 0);
}
