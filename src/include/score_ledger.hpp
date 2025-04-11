#ifndef PINKYTOE_IMPL_MOVE_LEDGER_HPP_
#define PINKYTOE_IMPL_MOVE_LEDGER_HPP_

#include <cstdint>

#include "meta.hpp"
#include "move_history.hpp"
#include "pinkytoe/enums.h"
#include "player.hpp"

namespace pinkytoe::impl {

class ScoreLedger final
{
  std::int8_t r_bals_[3];
  std::int8_t c_bals_[3];
  std::int8_t d_bals_[2];
  MoveHistory history_;

public:
  /// @brief First player config and MoveHistory ref required
  /// @param p1
  inline constexpr ScoreLedger(std::int8_t p1) noexcept
    : r_bals_{ 0 }
    , c_bals_{ 0 }
    , d_bals_{ 0 }
    , history_(p1)
  {
  }

  /// OPERATIONS

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

  /// PROPERTIES

  /// @brief Fetches last move in history
  /// @param r Stores last row index
  /// @param c Stores last column index
  inline constexpr void last_move(std::uint8_t& r,
                                  std::uint8_t& c) const noexcept
  {
    this->history_.top(r, c);
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
  this->r_bals_[r] += p;
  this->c_bals_[c] += p;

  /// Update diagonals
  auto on_diag0 = bool_as_integral<std::int8_t>(r == c);
  auto on_diag1 = bool_as_integral<std::int8_t>(r + c == 2);
  this->d_bals_[0] += on_diag0 * p;
  this->d_bals_[1] += on_diag1 * p;

  // Update move history
  this->history_.push(r, c);
}

/// @brief Removes last record from ledger
constexpr void
ScoreLedger::remove_last() noexcept
{
  /// Rollback balance factors based on last to play
  std::int8_t p = this->history_.last_player();

  /// Pop last move from history
  std::uint8_t r{}, c{};
  this->history_.pop(r, c);

  /// Rollback rows/columns
  this->r_bals_[r] -= p;
  this->c_bals_[c] -= p;

  /// Rollback diagonals
  auto on_diag0 = bool_as_integral<std::int8_t>(r == c);
  auto on_diag1 = bool_as_integral<std::int8_t>(r + c == 2);
  this->d_bals_[0] -= on_diag0 * p;
  this->d_bals_[1] -= on_diag1 * p;
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
  this->r_bals_[r] -= p;
  this->c_bals_[c] -= p;

  /// Rollback diagonals
  auto on_diag0 = bool_as_integral<std::int8_t>(r == c);
  auto on_diag1 = bool_as_integral<std::int8_t>(r + c == 2);
  this->d_bals_[0] -= on_diag0 * p;
  this->d_bals_[1] -= on_diag1 * p;
}

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_MOVE_LEDGER_HPP_
