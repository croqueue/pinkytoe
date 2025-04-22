#include "pinkytoe/basic_toe.h"
#include "pinkytoe/enums.h"
#include <cstdint>
#include <gtest/gtest.h>

using pinkytoe::BasicToe;
using pinkytoe::Column;
using pinkytoe::Player;
using pinkytoe::Row;

TEST(BasicToeTests, constructor_test)
{
  Player first_player = Player::X;
  BasicToe game(first_player);
  Row row{};
  Column column{};

  ASSERT_EQ(game.last_player(), Player::None);
  ASSERT_EQ(game.next_player(), first_player);
  ASSERT_EQ(game.move_count(), 0);
  ASSERT_EQ(game.last_move(row, column), false);
}
