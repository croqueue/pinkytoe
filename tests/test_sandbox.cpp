#include "libt3.hpp"
#include <gtest/gtest.h>
#include <random>
#include <vector>
#include <utility>
#include <tuple>

namespace libt3::tests {

using libt3::Player;
using libt3::TicTacToe;
using libt3::Column;
using libt3::Row;
using libt3::Result;

GTEST_TEST(TicTacToeBoardTests, PlayerXStarts)
{
  std::vector<std::tuple<Row, Column>> positions {
    { Row::Top,     Column::Left },
    { Row::Top,     Column::Middle },
    { Row::Top,     Column::Right },
    { Row::Middle,  Column::Left },
    { Row::Middle,  Column::Middle },
    { Row::Middle,  Column::Right },
    { Row::Bottom,  Column::Left },
    { Row::Bottom,  Column::Middle },
    { Row::Bottom,  Column::Right }
  };

  TicTacToe board;
  board.set_starting_player(Player::X);
  std::random_shuffle(positions.begin(), positions.end());

  ASSERT_FALSE(false);
}

} // namespace libt3::tests
