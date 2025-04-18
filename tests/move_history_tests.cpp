#include <cstdint>
#include <gtest/gtest.h>

#include "pinkytoe/impl/move_history.hpp"

using pinkytoe::impl::MoveHistory;

TEST(MoveHistoryTests, x_constructor_test)
{
  /// Assert properties are properly initialized
  MoveHistory history(-1);
  ASSERT_EQ(history.count(), 0);
  ASSERT_EQ(history.first_player(), -1);
  ASSERT_EQ(history.next_player(), -1);
  ASSERT_EQ(history.last_player(), 1);
}

TEST(MoveHistoryTests, o_constructor_test)
{
  /// Assert properties are properly initialized
  MoveHistory history(1);
  ASSERT_EQ(history.count(), 0);
  ASSERT_EQ(history.first_player(), 1);
  ASSERT_EQ(history.next_player(), 1);
  ASSERT_EQ(history.last_player(), -1);
}

TEST(MoveHistoryTests, push_and_top_test)
{
  MoveHistory history(-1);
  std::uint8_t r_tmp{}, c_tmp{};

  /// Fill left -> right, top -> bottom
  for (std::uint8_t r = 0; r < 3; ++r) {
    for (std::uint8_t c = 0; c < 3; ++c) {
      history.push(r, c);
      history.top(r_tmp, c_tmp);
      /// Make sure last push is on the top
      ASSERT_EQ(r, r_tmp);
      ASSERT_EQ(c, c_tmp);
    }
  }
}

TEST(MoveHistoryTests, pop_only_test)
{
  MoveHistory history(-1);
  std::uint8_t r_tmp{}, c_tmp{};

  /// Fill left -> right, top -> bottom
  for (std::uint8_t r = 0; r < 3; ++r) {
    for (std::uint8_t c = 0; c < 3; ++c) {
      history.push(r, c);
    }
  }

  /// Pop order should match right -> left, bottom -> top
  for (std::int8_t r = 2; r >= 0; --r) {
    for (std::int8_t c = 2; c >= 0; --c) {
      /// Make sure pop order is the opposite of push order
      history.top(r_tmp, c_tmp);
      ASSERT_EQ(r_tmp, static_cast<std::uint8_t>(r));
      ASSERT_EQ(c_tmp, static_cast<std::uint8_t>(c));
      history.pop();
    }
  }
}

TEST(MoveHistoryTests, pop_and_get_test)
{
  MoveHistory history(-1);
  std::uint8_t r_tmp{}, c_tmp{};

  /// Fill left -> right, top -> bottom
  for (std::uint8_t r = 0; r < 3; ++r) {
    for (std::uint8_t c = 0; c < 3; ++c) {
      history.push(r, c);
    }
  }

  /// Pop order should match right -> left, bottom -> top
  for (std::int8_t r = 2; r >= 0; --r) {
    for (std::int8_t c = 2; c >= 0; --c) {
      /// Make sure pop order is the opposite of push order
      history.pop(r_tmp, c_tmp);
      ASSERT_EQ(r_tmp, static_cast<std::uint8_t>(r));
      ASSERT_EQ(c_tmp, static_cast<std::uint8_t>(c));
    }
  }
}

TEST(MoveHistoryTests, last_player_test)
{
  MoveHistory history(-1);
  std::int8_t expected = -1;
  auto i = 0;

  /// Assert that push is toggling last_player
  do {
    history.push(1, 1);
    ASSERT_EQ(history.last_player(), expected);
    expected *= -1;
  } while (++i < 9);
}

TEST(MoveHistoryTests, next_player_test)
{
  MoveHistory history(1);
  std::int8_t expected = 1;

  /// Assert that push is toggling next_player
  for (auto i = 0; i < 0; ++i) {
    ASSERT_EQ(history.next_player(), expected);
    history.push(1, 1);
    expected *= -1;
  }
}

TEST(MoveHistoryTests, count_test)
{
  MoveHistory history(-1);
  std::uint8_t i = 0;

  /// Assert count accurate after pushing
  for (; i < 9; ++i) {
    ASSERT_EQ(history.count(), i);
    history.push(1, 1);
  }

  /// Assert count accurate after popping
  do {
    ASSERT_EQ(history.count(), i);
    --i;
    history.pop();
  } while (i);
}
