#include "pinkytoe/basic_toe.h"
#include "pinkytoe/enums.h"
#include "pinkytoe/impl/meta.hpp"
#include "pinkytoe/impl/position.hpp"
#include <cstdint>

namespace pinkytoe {

constexpr MoveResult
BasicToe::play_next(Row row, Column column) noexcept
{
  using impl::enum_as_integral;
  using impl::position_valid;

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

  /// TODO: implement LedgerStatus -> MoveResult method
  return this->gstat_.to_move_result();
}

constexpr MoveResult
BasicToe::undo_last() noexcept
{
  return MoveResult::Ok;
}

constexpr MoveResult
BasicToe::undo_last(Row& row, Column& column) noexcept
{
  return MoveResult::Ok;
}

constexpr void
BasicToe::read_board(Player outbuf[3][3]) const noexcept
{
  for (std::uint8_t i = 0; i < 3; ++i) {
    for (std::uint8_t j = 0; j < 3; ++j) {
      auto claimed_by = static_cast<Player>(this->frame_.get_square(i, j));
      outbuf[i][j] = claimed_by;
    }
  }
}

} // namespace pinkytoe
