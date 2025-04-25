#include "pinkytoe/api.h"
#include <cstdint>
#include <gtest/gtest.h>

using pinkytoe::Column;
using pinkytoe::Player;
using pinkytoe::Row;
using pinkytoe::TicTacToe;

TEST(TicTacToeTests, constructor_test)
{
  Player first_player = Player::X;
  TicTacToe game(first_player);
  Row row{};
  Column column{};

  ASSERT_EQ(game.last_player(), Player::None);
  ASSERT_EQ(game.next_player(), first_player);
  ASSERT_EQ(game.move_count(), 0);
  ASSERT_EQ(game.last_move(row, column), false);
}
