#ifndef PINKYTOE_IMPL_MOVE_LEDGER_HPP_
#define PINKYTOE_IMPL_MOVE_LEDGER_HPP_

#include <cstdint>

#include "pinkytoe/enums.h"
#include "meta.hpp"
#include "move_history.hpp"
#include "player.hpp"

namespace pinkytoe::impl
{

class MoveLedger final {
  Player first_player_;
  std::int8_t r_bals_[3]{};
  std::int8_t c_bals_[3]{};
  std::int8_t d_bals_[2]{};
  MoveHistory history_{};

public:

  /// @brief Configuration of first player required to construct
  /// @param first_player 
  inline constexpr MoveLedger(Player first_player) noexcept
    : first_player_(first_player)
  {
  }

  /// @brief Records next move
  /// @param r Row index
  /// @param c Column index
  inline constexpr void record_next(std::uint8_t r, std::uint8_t c) noexcept
  {
    using impl::bool_as_integral;
    using impl::enum_as_integral;
    using impl::whose_turn;
  
    // Update balances
    auto move_count = this->history_.count();
    auto player = whose_turn(this->first_player_, move_count);
    auto p = enum_as_integral(player);
  
    this->r_bals_[r] += p;
    this->c_bals_[c] += p;
  
    auto on_diag0 = bool_as_integral<std::int8_t>(r == c);
    auto on_diag1 = bool_as_integral<std::int8_t>(r + c == 2);
    this->d_bals_[0] += on_diag0 * p;
    this->d_bals_[1] += on_diag1 * p;
  
    // Add move to history
    this->history_.push(r, c);
  }

  /// @brief Removes last record from ledger
  inline constexpr void remove_last() noexcept
  {
    using impl::bool_as_integral;
    using impl::enum_as_integral;
    using impl::whose_turn;
  
    // Pop last move from history
    std::uint8_t r{}, c{};
    this->history_.pop(r, c);
  
    auto move_count = this->history_.count();
    auto player = whose_turn(this->first_player_, move_count);
    auto p = enum_as_integral(player);
  
    // Rollback balances
    this->r_bals_[r] -= p;
    this->c_bals_[c] -= p;
  
    auto on_diag0 = bool_as_integral<std::int8_t>(r == c);
    auto on_diag1 = bool_as_integral<std::int8_t>(r + c == 2);
    this->d_bals_[0] -= on_diag0 * p;
    this->d_bals_[1] -= on_diag1 * p;
  }

  /// @brief Removes last record from ledger
  /// @param r Stores removed row index
  /// @param c Stores removed row index
  inline constexpr void remove_last(std::uint8_t& r, std::uint8_t& c) noexcept
  {
    using impl::bool_as_integral;
    using impl::enum_as_integral;
    using impl::whose_turn;
  
    // Pop last move from history
    this->history_.pop(r, c);
  
    auto move_count = this->history_.count();
    auto player = whose_turn(this->first_player_, move_count);
    auto p = enum_as_integral(player);
  
    // Rollback balances
    this->r_bals_[r] -= p;
    this->c_bals_[c] -= p;
  
    auto on_diag0 = bool_as_integral<std::int8_t>(r == c);
    auto on_diag1 = bool_as_integral<std::int8_t>(r + c == 2);
    this->d_bals_[0] -= on_diag0 * p;
    this->d_bals_[1] -= on_diag1 * p;
  }

  /// @brief Returns number of moves currently recorded
  /// @return Number of recorded moves
  inline constexpr std::uint8_t move_count() noexcept
  {
    return this->history_.count();
  }

  /// @brief Returns the player configured to go first
  /// @return The player the moves/moved first
  inline constexpr Player first_player() noexcept
  {
    return this->first_player_;
  }
};

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_MOVE_LEDGER_HPP_
