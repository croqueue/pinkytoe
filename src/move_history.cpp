#include <cstdint>
#include "pinkytoe/move_history.h"
#include "position.h"

namespace pinkytoe
{

/// @brief Retrieves move position from the top of the stack 
/// @param r Stores row index from the top of the stack
/// @param c Stores column index from the top of the stack
constexpr void MoveHistory::top(std::uint8_t& r, std::uint8_t& c) const noexcept
{
  using impl::index_to_position;

  auto top_index = this->count_ - 1;
  std::uint8_t byte_index = top_index >> 1;
  auto shift = (top_index & 1) << 2;
  std::uint8_t frame_pos = (this->data_[byte_index] >> shift) & 15;
  index_to_position(frame_pos, r, c);
}

/// @brief Adds next move to history 
/// @param r Row index
/// @param c Column index
constexpr void MoveHistory::push(std::uint8_t r, std::uint8_t c) noexcept
{
  using impl::position_to_index;

  std::uint8_t frame_pos = position_to_index(r, c);
  std::uint8_t byte_index = this->count_ >> 1;
  auto shift = (this->count_ & 1) << 2;
  this->data_[byte_index] &= ~0u >> shift;
  this->data_[byte_index] |= frame_pos << shift;
  ++this->count_;
}

/// @brief Removes last move from history
constexpr void MoveHistory::pop() noexcept
{
  --this->count_;
}

/// @brief Removes last move from history
/// @param r Stores popped row index
/// @param c Stores popped column index
constexpr void MoveHistory::pop(std::uint8_t& r, std::uint8_t& c) noexcept
{
  using impl::index_to_position;

  --this->count_;
  std::uint8_t byte_index = this->count_ >> 1;
  auto shift = (this->count_ & 1) << 2;
  std::uint8_t frame_pos = (this->data_[byte_index] >> shift) & 15;
  index_to_position(frame_pos, r, c);
}

/// @brief Returns number of moves currently recorded
/// @return Number of recorded moves
constexpr std::uint8_t MoveHistory::move_count() const noexcept
{
  return this->count_;
}

} // namespace pinkytoe
