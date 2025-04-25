#include "pinkytoe/impl/score_ledger.hpp"
#include <gtest/gtest.h>

using pinkytoe::impl::LineDirection;
using pinkytoe::impl::ScoreLedger;

TEST(ScoreLedgerTests, constructor_test)
{
  ScoreLedger ledger(-1);
  ASSERT_EQ(ledger.move_count(), 0);
  ASSERT_EQ(ledger.next_player(), -1);
  ASSERT_EQ(ledger.last_player(), 1);
}

TEST(ScoreLedgerTests, x_horizontal_win_test)
{
  ScoreLedger ledger(-1);
  ScoreLedger::Status status;

  /// X claims bottom-middle square
  ledger.record_next(2, 1);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O claims center square
  ledger.record_next(1, 1);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X claims bottom-right square
  ledger.record_next(2, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O claims top-right square
  ledger.record_next(0, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X claims bottom-left square (winning move)
  ledger.record_next(2, 0);
  ledger.check_status(status);

  /// Status should reflect that X claimed the bottom row
  ASSERT_EQ(status.winner, -1);
  ASSERT_EQ(status.line_dir, LineDirection::Horizontal);
  ASSERT_EQ(status.line_pos, 2);
}

TEST(ScoreLedgerTests, o_horizontal_win_test)
{
  ScoreLedger ledger(1);
  ScoreLedger::Status status;

  /// O claims center square
  ledger.record_next(1, 1);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X claims bottom-middle square
  ledger.record_next(2, 1);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O claims middle-left square
  ledger.record_next(1, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X claims bottom-left square
  ledger.record_next(2, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// 0 claims middle-right square (winning move)
  ledger.record_next(1, 2);
  ledger.check_status(status);

  /// Status should reflect that O claimed the middle row
  ASSERT_EQ(status.winner, 1);
  ASSERT_EQ(status.line_dir, LineDirection::Horizontal);
  ASSERT_EQ(status.line_pos, 1);
}

TEST(ScoreLedgerTests, x_vertical_win_test)
{
  ScoreLedger ledger(1);
  ScoreLedger::Status status;

  /// O claims center square
  ledger.record_next(1, 1);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X claims the top-right square
  ledger.record_next(0, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O claims the middle-left square
  ledger.record_next(1, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X claims the bottom-right square
  ledger.record_next(2, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O claims the bottom-left square
  ledger.record_next(2, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X claims middle-right square (winning move)
  ledger.record_next(1, 2);
  ledger.check_status(status);

  /// Status should reflect that X won the right column
  ASSERT_EQ(status.winner, -1);
  ASSERT_EQ(status.line_dir, LineDirection::Vertical);
  ASSERT_EQ(status.line_pos, 2);
}

TEST(ScoreLedgerTests, o_vertical_win_test)
{
  ScoreLedger ledger(-1);
  ScoreLedger::Status status;

  /// X claims center square
  ledger.record_next(1, 1);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// 0 claims the top-left square
  ledger.record_next(0, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X claims the middle-right square
  ledger.record_next(1, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O claims the bottom-left square
  ledger.record_next(2, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X claims the bottom-right square
  ledger.record_next(2, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O claims middle-left square (winning move)
  ledger.record_next(1, 0);
  ledger.check_status(status);

  /// Status should reflect that X won the right column
  ASSERT_EQ(status.winner, 1);
  ASSERT_EQ(status.line_dir, LineDirection::Vertical);
  ASSERT_EQ(status.line_pos, 0);
}

TEST(ScoreLedgerTests, x_diagonal_win_test)
{
  ScoreLedger ledger(-1); // -1 = Player::X starts
  ScoreLedger::Status status;

  /// X plays center square
  ledger.record_next(1, 1);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O plays middle-left square
  ledger.record_next(1, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X plays bottom-right square
  ledger.record_next(2, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O plays middle-right square
  ledger.record_next(1, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X plays top-left square (winning move)
  ledger.record_next(0, 0);

  /// Status should show that X won the main diagonal
  ledger.check_status(status);
  ASSERT_EQ(status.winner, -1);
  ASSERT_EQ(status.line_dir, LineDirection::Diagonal);
  ASSERT_EQ(status.line_pos, 0);
}

TEST(ScoreLedgerTests, o_diagonal_win_test)
{
  ScoreLedger ledger(1); // 1 = Player::O starts
  ScoreLedger::Status status;

  /// O plays center square
  ledger.record_next(1, 1);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X plays middle-left square
  ledger.record_next(1, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O plays bottom-right square
  ledger.record_next(2, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X plays middle-right square
  ledger.record_next(1, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O plays top-left square (winning move)
  ledger.record_next(0, 0);

  /// Status should show that O won the main diagonal
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 1);
  ASSERT_EQ(status.line_dir, LineDirection::Diagonal);
  ASSERT_EQ(status.line_pos, 0);
}

TEST(ScoreLedgerTests, x_antidiagonal_win_test)
{
  ScoreLedger ledger(-1); // -1 = Player::X starts
  ScoreLedger::Status status;

  /// X plays top-right square
  ledger.record_next(0, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O plays bottom-right square
  ledger.record_next(2, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X plays bottom-left square
  ledger.record_next(2, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O plays top-left square
  ledger.record_next(0, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X plays center square (winning move)
  ledger.record_next(1, 1);

  /// Status should show that X won the antidiagonal
  ledger.check_status(status);
  ASSERT_EQ(status.winner, -1);
  ASSERT_EQ(status.line_dir, LineDirection::Diagonal);
  ASSERT_EQ(status.line_pos, 1);
}

TEST(ScoreLedgerTests, o_antidiagonal_win_test)
{
  ScoreLedger ledger(1); // 1 = Player::O starts
  ScoreLedger::Status status;

  /// O plays top-right square
  ledger.record_next(0, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X plays bottom-right square
  ledger.record_next(2, 2);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O plays bottom-left square
  ledger.record_next(2, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// X plays top-left square
  ledger.record_next(0, 0);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);

  /// O plays center square (winning move)
  ledger.record_next(1, 1);

  /// Status should show that O won the antidiagonal
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 1);
  ASSERT_EQ(status.line_dir, LineDirection::Diagonal);
  ASSERT_EQ(status.line_pos, 1);
}

TEST(ScoreLedgerTests, last_move_test)
{
  ScoreLedger ledger(-1);
  ScoreLedger::Status status;
  constexpr auto move_count = 3;

  const std::uint8_t r[3] = { 0, 0, 1 };
  const std::uint8_t c[3] = { 1, 2, 0 };
  std::uint8_t r_tmp{}, c_tmp{};

  ledger.record_next(r[0], c[0]);

  for (auto i = 1; i < move_count; ++i) {
    ledger.last_move(r_tmp, c_tmp);
    ASSERT_EQ(r_tmp, r[i - 1]);
    ASSERT_EQ(c_tmp, c[i - 1]);
    ledger.record_next(r[i], c[i]);
  }

  ledger.last_move(r_tmp, c_tmp);
  ASSERT_EQ(r_tmp, r[move_count - 1]);
  ASSERT_EQ(c_tmp, c[move_count - 1]);
}

TEST(ScoreLedgerTests, remove_last_test)
{
  ScoreLedger ledger(-1); // -1 = Player::X starts
  ScoreLedger::Status status;
  std::uint8_t r{}, c{}, r_tmp{}, c_tmp{};

  /// Players fill board top -> bottom, left -> right
  for (std::uint8_t move = 0; move < 8; ++move) {
    r = move / 3u;
    c = move % 3u;
    ledger.record_next(r, c);
    ledger.check_status(status);
    if (status.winner != 0)
      break;
    ledger.remove_last(r_tmp, c_tmp);
    ASSERT_EQ(r, r_tmp);
    ASSERT_EQ(c, c_tmp);
    ledger.record_next(r, c);
  }

  /// X should have won the antidiagonal
  ASSERT_EQ(status.winner, -1);
  ASSERT_EQ(status.line_dir, LineDirection::Diagonal);
  ASSERT_EQ(status.line_pos, 1);

  /// Undo the win (should revert winner status)
  ledger.remove_last(r_tmp, c_tmp);
  ledger.check_status(status);
  ASSERT_EQ(status.winner, 0);
}
