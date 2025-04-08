#ifndef PINKYTOE_IMPL_MOVE_HISTORY_HPP_
#define PINKYTOE_IMPL_MOVE_HISTORY_HPP_

#include <cstdint>

#include "position.hpp"

namespace pinkytoe::impl
{

/// @brief Tracks player choices over the course of a game
class MoveHistory final {
  /// Each choice is 4 bits x 9 maximum choices for a game = 36 bits
  std::uint8_t data_[5];
  std::uint8_t count_;

public:
  /// @brief Initializes empty history
  inline constexpr MoveHistory() noexcept
    : data_{0}
    , count_{0}
  {
  }

  /// @brief Retrieves move position from the top of the stack 
  /// @param r Stores row index from the top of the stack
  /// @param c Stores column index from the top of the stack
  inline constexpr void top(std::uint8_t& r, std::uint8_t& c) const noexcept
  {
    using impl::index_to_rc;
  
    auto top_index = this->count_ - 1;
    std::uint8_t byte_index = top_index >> 1;
    auto shift = (top_index & 1) << 2;
    std::uint8_t frame_pos = (this->data_[byte_index] >> shift) & 15;
    index_to_rc(frame_pos, r, c);
  }

  /// @brief Adds next move to history 
  /// @param r Row index
  /// @param c Column index
  inline constexpr void push(std::uint8_t r, std::uint8_t c) noexcept
  {
    using impl::rc_to_index;
    std::uint8_t frame_pos = rc_to_index(r, c);
    std::uint8_t byte_index = this->count_ >> 1;
    auto shift = (this->count_ & 1) << 2;
    this->data_[byte_index] &= ~0u >> shift;
    this->data_[byte_index] |= frame_pos << shift;
    ++this->count_;
  }

  /// @brief Removes last move from history
  inline constexpr void pop() noexcept
  {
    --this->count_;
  }

  /// @brief Removes last move from history
  /// @param r Stores popped row index
  /// @param c Stores popped column index
  inline constexpr void pop(std::uint8_t& r, std::uint8_t& c) noexcept
  {
    using impl::index_to_rc;
  
    --this->count_;
    std::uint8_t byte_index = this->count_ >> 1;
    auto shift = (this->count_ & 1) << 2;
    std::uint8_t frame_pos = (this->data_[byte_index] >> shift) & 15;
    index_to_rc(frame_pos, r, c);
  }

  /// @brief Returns number of moves currently recorded
  /// @return Number of recorded moves
  inline constexpr std::uint8_t count() const noexcept
  {
    return this->count_;
  }
};

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_MOVE_HISTORY_HPP_
