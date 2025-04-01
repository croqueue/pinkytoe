#include "pinkytoe/enums.h"
#include "meta.hpp"
#include "move_ledger.h"
#include "player.h"

namespace pinkytoe::impl
{

constexpr BoardPosition::BoardPosition(Row r, Column c) noexcept
  : r(enum_as_integral(r))
  , c(enum_as_integral(c))
{
}

constexpr MoveLedger::MoveLedger(Player start_player) noexcept
  : balance_{}, history_{}, move_count_{}, start_player_(start_player)
{
}

constexpr MoveLedger::Status MoveLedger::move_next(Row r, Column c) noexcept
{
  // Update balances
  auto player = current_player(this->start_player_, this->move_count_);
  auto p = enum_as_integral(player);

  


  // Add move to history
  this->history_[this->move_count_] = BoardPosition(r, c);


  // Increment move count
  ++this->move_count_;
}

constexpr MoveLedger::Status MoveLedger::undo_last() noexcept
{
  ;
}

constexpr std::uint8_t MoveLedger::move_count() noexcept
{
  return this->move_count_;
}

constexpr Player MoveLedger::start_player() noexcept
{
  return this->start_player_;
}

} // namespace pinkytoe::impl
