#include "score_ledger.hpp"
#include <gtest/gtest.h>

using pinkytoe::impl::ScoreLedger;

TEST(ScoreLedgerTests, constructor_test)
{
  ScoreLedger ledger(-1);
  ASSERT_EQ(ledger.move_count(), 0);
}
