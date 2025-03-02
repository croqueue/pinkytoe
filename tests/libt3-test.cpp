#include "libt3.hpp"
#include <gtest/gtest.h>

namespace libt3::tests {

using libt3::CellOwner;
using libt3::TicTacToeBoard;

GTEST_TEST(TicTacToeBoardTests, PlayerXStarts)
{
  TicTacToeBoard board(CellOwner::PlayerX);
  ASSERT_FALSE(false);
}

GTEST_TEST(TicTacToeBoardTests, PlayerOStarts)
{
  TicTacToeBoard board(CellOwner::PlayerO);
  ASSERT_FALSE(false);
}

} // namespace libt3::tests
