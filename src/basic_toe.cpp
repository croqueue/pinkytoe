#include "pinkytoe/impl/basic_toe.hpp"
#include "pinkytoe/impl/enums.hpp"
#include "pinkytoe/impl/meta.hpp"
#include "pinkytoe/impl/position.hpp"
#include <cstdint>

namespace pinkytoe::impl {

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
  std::uint8_t r{}, c{};

  if (this->ledger_.move_count() == 0)
    return MoveResult::CannotUndo;

  this->ledger_.remove_last(r, c);
  this->frame_.set_square(r, c, 0);
  return MoveResult::Ok;
}

constexpr MoveResult
BasicToe::undo_last(Row& row, Column& column) noexcept
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

} // namespace pinkytoe::impl
