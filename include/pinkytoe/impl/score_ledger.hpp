#ifndef PINKYTOE_IMPL_SCORE_LEDGER_HPP_
#define PINKYTOE_IMPL_SCORE_LEDGER_HPP_

#include <cstdint>

#include "pinkytoe/enums.h"
#include "pinkytoe/impl/meta.hpp"
#include "pinkytoe/impl/move_history.hpp"
#include "player.hpp"

namespace pinkytoe::impl {

/// @brief
enum class LineDirection : std::uint8_t
{
  Horizontal = 0,
  Vertical = 1,
  Diagonal = 2
};

/// @brief
struct LedgerStatus final
{
  /// @brief
  std::uint8_t move_count;
  /// @brief Indicates winner (-1=X, 0=None, or 1=O)
  std::int8_t winner;
  /// @brief Indicates direction of winning line (garbage if `winner == 0`)
  LineDirection line_dir;
  /// @brief Value `0..2` for horizontal/vertical, `0..1` for diagonal
  std::uint8_t line_pos;

  inline constexpr LedgerStatus() noexcept
    : move_count{}
    , winner{}
    , line_dir{}
    , line_pos{}
  {
  }

  /// @brief TODO: impl
  /// @return
  inline constexpr MoveResult to_move_result() const noexcept
  {
    std::uint8_t result{};

    switch (this->winner) {
      case -1:

        break;
      case 1:
        break;
      default:
        break;
    }
  }
};

class ScoreLedger final
{
  std::int8_t balances_[3][3];
  MoveHistory history_;

  /// @brief
  /// @tparam LineDir
  /// @param status
  /// @return
  template<LineDirection LineDir>
  inline constexpr void check_direction(LedgerStatus& status) const noexcept;

  /// @brief
  /// @tparam LineDir
  /// @tparam LinePos
  /// @param status
  template<LineDirection LineDir, std::uint8_t LinePos>
  constexpr void check_line(LedgerStatus& status) const noexcept;

public:
  /// @brief First player config required
  /// @param p1
  inline constexpr ScoreLedger(std::int8_t p1) noexcept
    : balances_{ 0 }
    , history_(p1)
  {
  }

  /// [OPS]

  /// @brief Records next move
  /// @param r Row index
  /// @param c Column index
  inline constexpr void record_next(std::uint8_t r, std::uint8_t c) noexcept;

  /// @brief Removes last record from ledger
  inline constexpr void remove_last() noexcept;

  /// @brief Removes last record from ledger and stores removed position
  /// @param r Stores row index of removed record
  /// @param c Stores column index of removed record
  inline constexpr void remove_last(std::uint8_t& r, std::uint8_t& c) noexcept;

  /// @brief Checks current status of the game according to the ledger
  /// @param status Mutable reference to status fields object
  inline constexpr void check_status(LedgerStatus& status) const noexcept;

  /// [PROPS]

  /// @brief Fetches last move in history
  /// @param r Stores last row index
  /// @param c Stores last column index
  inline constexpr void last_move(std::uint8_t& r,
                                  std::uint8_t& c) const noexcept
  {
    this->history_.top(r, c);
  }

  inline constexpr void last_move(Row& row, Column& column) const noexcept
  {
    this->history_.top(row, column);
  }

  /// @brief Player that moved last
  /// @return Player enumeration value
  inline constexpr std::int8_t last_player() const noexcept
  {
    return this->history_.last_player();
  }

  /// @brief Player that moves next
  /// @return Player enumeration value
  inline constexpr std::int8_t next_player() const noexcept
  {
    return this->history_.next_player();
  }

  /// @brief Returns number of moves currently recorded
  /// @return Number of recorded moves
  inline constexpr std::uint8_t move_count() const noexcept
  {
    return this->history_.count();
  }
};

/// @brief Records next move
/// @param r Row index
/// @param c Column index
constexpr void
ScoreLedger::record_next(std::uint8_t r, std::uint8_t c) noexcept
{
  /// Update balance factors based on next to play
  std::int8_t p = this->history_.next_player();

  /// Update rows/columns
  this->balances_[0][r] += p;
  this->balances_[1][c] += p;

  /// Update diagonals
  this->balances_[2][0] += p * bool_as_integral<std::int8_t>(r == c);
  this->balances_[2][1] += p * bool_as_integral<std::int8_t>(r + c == 2);

  // Update move history
  this->history_.push(r, c);
}

/// @brief Removes last record from ledger
constexpr void
ScoreLedger::remove_last() noexcept
{
  std::uint8_t r{}, c{};
  this->remove_last(r, c);
}

/// @brief Removes last record from ledger and stores removed position
/// @param r Stores row index of removed record
/// @param c Stores column index of removed record
constexpr void
ScoreLedger::remove_last(std::uint8_t& r, std::uint8_t& c) noexcept
{
  /// Rollback balance factors based on last to play
  std::int8_t p = this->history_.last_player();

  /// Pop last move from history
  this->history_.pop(r, c);

  /// Rollback rows/columns
  this->balances_[0][r] -= p;
  this->balances_[1][c] -= p;

  /// Rollback diagonals
  this->balances_[2][0] -= p * bool_as_integral<std::int8_t>(r == c);
  this->balances_[2][1] -= p * bool_as_integral<std::int8_t>(r + c == 2);
}

/// @brief Checks current status of the game according to the ledger
/// @param status Mutable reference to status fields object
constexpr void
ScoreLedger::check_status(LedgerStatus& status) const noexcept
{
  status.move_count = this->history_.count();
  status.winner = 0;
  status.line_dir = LineDirection::Horizontal;
  status.line_pos = 0;
  this->check_direction<LineDirection::Horizontal>(status);
  this->check_direction<LineDirection::Vertical>(status);
  this->check_direction<LineDirection::Diagonal>(status);
}

template<LineDirection LineDir>
constexpr void
ScoreLedger::check_direction(LedgerStatus& status) const noexcept
{
  this->check_line<LineDir, 0>(status);
  this->check_line<LineDir, 1>(status);

  if constexpr (LineDir != LineDirection::Diagonal) {
    this->check_line<LineDir, 2>(status);
  }
}

template<LineDirection LineDir, std::uint8_t LinePos>
constexpr void
ScoreLedger::check_line(LedgerStatus& status) const noexcept
{
  /// Determine winner at position/direction (or none)
  auto ld_int = enum_as_integral(LineDir);
  auto value = this->balances_[ld_int][LinePos];
  auto x_claimed = bool_as_integral<std::uint8_t>(value == -3);
  auto o_claimed = bool_as_integral<std::uint8_t>(value == 3);
  std::uint8_t line_claimed = x_claimed | o_claimed;
  status.winner |= o_claimed - x_claimed;
  /// Update line direction/position
  ld_int *= line_claimed;
  ld_int |= enum_as_integral(status.line_dir);
  status.line_dir = static_cast<LineDirection>(ld_int);
  status.line_pos |= LinePos * line_claimed;
}

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_SCORE_LEDGER_HPP_
