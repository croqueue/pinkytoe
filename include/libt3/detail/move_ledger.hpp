#ifndef LIBT3_DETAIL_MOVE_LEDGER_HPP_
#define LIBT3_DETAIL_MOVE_LEDGER_HPP_

#include <cstdint>
#include <cmath>
#include "libt3/enums.hpp"
#include "libt3/detail/common.hpp"

namespace libt3::detail
{

/// @brief 
/// @param player 
/// @return 
inline constexpr Player flip_player(Player player) noexcept
{
  return static_cast<Player>(enum_as_integral(player) * -1);
}

/// @brief 
class MoveLedger final
{
  /// @brief 
  struct BoardPosition final {
    Row r;
    Column c;

    /// @brief 
    BoardPosition() = default;

    /// @brief 
    /// @param r 
    /// @param c 
    inline constexpr BoardPosition(Row r, Column c) noexcept
      : r(r)
      , c(c)
    {
    }
  };

  struct BalanceTable final {
    // 24 bits
    std::int8_t row0 : 3;
    std::int8_t row1 : 3;
    std::int8_t row2 : 3;
    std::int8_t col0 : 3;
    std::int8_t col1 : 3;
    std::int8_t col2 : 3;
    std::int8_t diag0 : 3;
    std::int8_t diag1 : 3;

    BalanceTable() = default;
  };

  BoardPosition move_history_[9]{};
  std::int8_t player_tbl_[2]{}; // <=== THIS IS DUMB
  std::uint8_t move_count_{};
  BalanceTable bal_tbl_{};
  // std::int8_t r_bals_[3]{};
  // std::int8_t c_bals_[3]{};
  // std::int8_t d_bals_[2]{};

  /// @brief Integral value of the next player to move
  inline constexpr std::int8_t next_player() noexcept;

  /// @brief Integral value of the last player to move
  inline constexpr std::int8_t last_player() noexcept;

  /// @brief Last position placed on the board 
  inline constexpr BoardPosition& last_position() noexcept;

  /// @brief Indicates whether or not a player has won
  inline constexpr Status check_status() noexcept;

public:
  /// @brief 
  /// @param start_player 
  inline constexpr MoveLedger(Player start_player) noexcept;

  /// @brief 
  /// @param pos 
  /// @return 
  inline constexpr Status record_move(Row row, Column column) noexcept;

  /// @brief 
  /// @return 
  inline constexpr Status undo_last() noexcept;
};

constexpr MoveLedger::MoveLedger(Player start_player) noexcept
{
  auto player1 = enum_as_integral(start_player);
  this->player_tbl_[0] = player1;
  this->player_tbl_[1] = player1 * -1;
}

constexpr Status MoveLedger::record_move(Row row, Column column) noexcept
{
  // Update balance factors
  auto p = this->next_player();
  auto r = enum_as_integral(row);
  auto c = enum_as_integral(column);
  
  // Update row/column/diagonal balances
  this->r_bals_[r] += p;
  this->c_bals_[c] += p;
  this->d_bals_[0] += p * bool_as_integral<std::int8_t>(r == c);
  this->d_bals_[1] += p * bool_as_integral<std::int8_t>(r == 2 - c);

  // Add move to history
  this->move_history_[this->move_count_] = BoardPosition(row, column);
  ++this->move_count_;
  
  return this->check_status();
}

constexpr Status MoveLedger::undo_last() noexcept
{
  // Validate operation
  if (this->move_count_ == 0)
    return Status::CantUndo;

  auto last_pos = this->last_position();
  auto p = this->last_player();

  // Revert balance factors
  auto r = enum_as_integral(last_pos.r);
  auto c = enum_as_integral(last_pos.c);

  this->r_bals_[r] -= p;
  this->c_bals_[c] -= p;
  this->d_bals_[0] -= p * bool_as_integral<std::int8_t>(r == c);
  this->d_bals_[1] -= p * bool_as_integral<std::int8_t>(r == 2 - c);
  
  // Pop last move off of history
  --this->move_count_;
  return Status::Ok;
}

/// @brief Integral value of the next player to move
constexpr std::int8_t MoveLedger::next_player() noexcept
{
  auto move_parity = this->move_count_ & 1;
  return this->player_tbl_[move_parity];
}

/// @brief Integral value of the last player to move
constexpr std::int8_t MoveLedger::last_player() noexcept
{
  auto move_parity = (this->move_count_ & 1) ^ 1;
  return this->player_tbl_[move_parity];
}

/// @brief Last position placed on the board 
constexpr MoveLedger::BoardPosition& MoveLedger::last_position() noexcept
{
  return this->move_history_[this->move_count_ - 1];
}

constexpr Status MoveLedger::check_status() noexcept
{
  for (auto i = 0; i < 3; ++i) {
    auto r_bal = this->r_bals_[i];
    switch (r_bal) {
    case 3:
      return Status::PlayerXWins;
    case -3:
      return Status::PlayerOWins;
    default:
      break;
    }
  }

  // if (this->r_bals_[0])

  for (auto i = 0; i < 3; ++i) {
    auto c_bal = this->c_bals_[i];
    switch (c_bal) {
    case 3:
      return Status::PlayerXWins;
    case -3:
      return Status::PlayerOWins;
    default:
      break;
    }
  }

  for (auto i = 0; i < 2; ++i) {
    auto d_bal = this->d_bals_[i];
    switch (d_bal) {
      case 3:
        return Status::PlayerXWins;
      case -3:
        return Status::PlayerOWins;
      default:
        break;
    }
  }

  return Status::Ok;
}

} // namespace libt3::detail

#endif // !LIBT3_DETAIL_MOVE_LEDGER_HPP_
