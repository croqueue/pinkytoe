#pragma once

#include "pinkytoe/impl/enums.hpp"
#include "pinkytoe/impl/frame.hpp"
#include "pinkytoe/impl/meta.hpp"
#include "pinkytoe/impl/score_ledger.hpp"
#include <cstdint>

namespace pinkytoe::impl {

class BasicToe final
{
  Frame frame_;
  ScoreLedger ledger_;
  mutable ScoreLedger::Status gstat_;

  inline constexpr BasicToe() noexcept
    : frame_{}
    , ledger_{}
    , gstat_{}
  {
  }

  inline constexpr void set_first_player(Player first_player) noexcept
  {
    this->ledger_.set_p1(enum_as_integral(first_player));
  }

  friend class UltimateToe;

public:
  inline explicit constexpr BasicToe(Player first_player) noexcept
    : frame_{}
    , ledger_(impl::enum_as_integral(first_player))
    , gstat_{}
  {
  }

  /// [ OPS ] ///

  /// @brief
  /// @param row
  /// @param column
  /// @return
  inline constexpr MoveResult play_next(Row row, Column column) noexcept
  {
    /// Validate state and input compatibility
    std::uint8_t r = enum_as_integral(row);
    std::uint8_t c = enum_as_integral(column);
    auto claimed_by = this->frame_.get_square(r, c);

    if (claimed_by != 0)
      return MoveResult::SquareOccupied;
    else if (this->ledger_.move_count() == 9)
      return MoveResult::GameIsOver;
    else if (!position_valid(r, c))
      return MoveResult::InvalidPosition;

    /// Update frame
    this->frame_.set_square(r, c, this->ledger_.next_player());

    /// Record move in score ledger
    this->ledger_.record_next(r, c);
    this->ledger_.check_status(this->gstat_);
    return this->gstat_.to_move_result();
  }

  /// @brief
  /// @return
  inline constexpr MoveResult undo_last() noexcept
  {
    std::uint8_t r{}, c{};

    if (this->ledger_.move_count() == 0)
      return MoveResult::CannotUndo;

    this->ledger_.remove_last(r, c);
    this->frame_.set_square(r, c, 0);
    return MoveResult::Ok;
  }

  /// @brief
  /// @param row
  /// @param column
  /// @return
  inline constexpr MoveResult undo_last(Row& row, Column& column) noexcept
  {
    std::uint8_t r{}, c{};

    if (this->ledger_.move_count() == 0)
      return MoveResult::CannotUndo;

    this->ledger_.remove_last(r, c);
    this->frame_.set_square(r, c, 0);
    row = static_cast<Row>(r);
    column = static_cast<Column>(c);
    return MoveResult::Ok;
  }

  /// @brief
  /// @param outbuf
  inline constexpr void read_board(Player outbuf[3][3]) const noexcept
  {
    for (std::uint8_t i = 0; i < 3; ++i) {
      for (std::uint8_t j = 0; j < 3; ++j) {
        auto claimed_by = static_cast<Player>(this->frame_.get_square(i, j));
        outbuf[i][j] = claimed_by;
      }
    }
  }

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

} // namespace pinkytoe::impl
