#include <gtest/gtest.h>

#include "score_ledger.hpp"

using pinkytoe::impl::LedgerStatus;
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
  // winner starts
}

TEST(ScoreLedgerTests, o_horizontal_win_test)
{
  // winner starts
}

TEST(ScoreLedgerTests, x_vertical_win_test)
{
  // loser starts
}

TEST(ScoreLedgerTests, o_vertical_win_test)
{
  // loser starts
}

TEST(ScoreLedgerTests, x_diagonal_win_test)
{
  ScoreLedger ledger(-1); // -1 = Player::X starts
  LedgerStatus status;

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
  // loser starts
}

TEST(ScoreLedgerTests, x_antidiagonal_win_test)
{
  // loser starts
}

TEST(ScoreLedgerTests, o_antidiagonal_win_test)
{
  ScoreLedger ledger(1); // 1 = Player::O starts
  LedgerStatus status;

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
  // ScoreLedger ledger(1); // 1 = Player::O starts
  // LedgerStatus status;
  // std::uint8_t r_tmp{}, c_tmp{};

  /// TODO: stuff
}

TEST(ScoreLedgerTests, remove_last_test)
{
  ScoreLedger ledger(-1); // -1 = Player::X starts
  LedgerStatus status;
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
