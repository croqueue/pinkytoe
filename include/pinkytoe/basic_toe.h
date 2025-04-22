#ifndef PINKYTOE_BASIC_TOE_H_
#define PINKYTOE_BASIC_TOE_H_

#include "pinkytoe/enums.h"
#include "pinkytoe/impl/frame.hpp"
#include "pinkytoe/impl/meta.hpp"
#include "pinkytoe/impl/score_ledger.hpp"
#include <cstdint>

namespace pinkytoe {

class BasicToe final
{
  // using impl::Frame;
  // using impl::ScoreLedger;
  // using impl::LedgerStatus;

  impl::Frame frame_;
  impl::ScoreLedger ledger_;
  mutable impl::LedgerStatus gstat_;

public:
  inline explicit constexpr BasicToe(Player first_player) noexcept
    : frame_{}
    , ledger_(impl::enum_as_integral(first_player))
  {
  }

  /// [OPS] ///

  /// @brief
  /// @param row
  /// @param column
  /// @return
  constexpr MoveResult play_next(Row row, Column column) noexcept;

  /// @brief
  /// @return
  constexpr MoveResult undo_last() noexcept;

  /// @brief
  /// @param row
  /// @param column
  /// @return
  constexpr MoveResult undo_last(Row& row, Column& column) noexcept;

  /// @brief
  /// @param outbuf
  constexpr void read_board(Player outbuf[3][3]) const noexcept;

  /// [PROPS] ///

  /// @brief
  /// @return
  inline constexpr Player next_player() const noexcept
  {
    this->ledger_.check_status(this->gstat_);

    if (this->gstat_.winner != 0 || this->gstat_.move_count == 9)
      return Player::None;

    return static_cast<Player>(this->ledger_.next_player());
  }

  /// @brief
  /// @return
  inline constexpr Player last_player() const noexcept
  {
    this->ledger_.check_status(this->gstat_);

    if (this->gstat_.move_count == 0)
      return Player::None;

    return static_cast<Player>(this->ledger_.last_player());
  }

  /// @brief
  /// @param row
  /// @param column
  /// @return
  inline constexpr bool last_move(Row& row, Column& column) const noexcept
  {
    if (this->ledger_.move_count() == 0)
      return false;

    this->ledger_.last_move(row, column);
    return true;
  }

  /// @brief
  /// @return
  inline constexpr std::uint8_t move_count() const noexcept
  {
    return this->ledger_.move_count();
  }
};

} // namespace pinkytoe

#endif // !PINKYTOE_BASIC_TOE_H_
