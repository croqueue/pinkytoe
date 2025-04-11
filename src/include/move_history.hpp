#ifndef PINKYTOE_IMPL_MOVE_HISTORY_HPP_
#define PINKYTOE_IMPL_MOVE_HISTORY_HPP_

#include <cstdint>

#include "player.hpp"
#include "position.hpp"

namespace pinkytoe::impl {

/// @brief Tracks player choices over the course of a game
class MoveHistory final
{
  std::uint8_t data_[5]; // 9 maximum choices for a game = 36 bits required
  std::uint8_t count_;
  std::int8_t p1_;

public:
  /// @brief Initializes empty history
  inline constexpr MoveHistory(std::int8_t p1) noexcept
    : data_{}
    , count_{}
    , p1_(p1)
  {
  }

  /// @brief Retrieves move position from the top of the stack
  /// @param r Stores row index from the top of the stack
  /// @param c Stores column index from the top of the stack
  inline constexpr void top(std::uint8_t& r, std::uint8_t& c) const noexcept;

  /// @brief Adds next move to history
  /// @param r Row index
  /// @param c Column index
  inline constexpr void push(std::uint8_t r, std::uint8_t c) noexcept;

  /// @brief Removes last move from history
  inline constexpr void pop() noexcept { --this->count_; }

  /// @brief Removes last move from history
  /// @param r Stores popped row index
  /// @param c Stores popped column index
  inline constexpr void pop(std::uint8_t& r, std::uint8_t& c) noexcept;

  /// @brief Returns number of moves currently recorded
  /// @return Number of recorded moves
  inline constexpr std::uint8_t count() const noexcept { return this->count_; }

  /// @brief Returns the configured first player
  /// @return Integral value corresponding to `pinkytoe::Player` enumeration
  inline constexpr std::int8_t first_player() const noexcept
  {
    return this->p1_;
  }

  /// @brief Last player to move
  /// @return Integral value corresponding to `pinkytoe::Player` enumeration
  inline constexpr std::int8_t last_player() const noexcept
  {
    return calculate_turn(this->p1_, this->count_ - 1);
  }

  /// @brief Next player to move
  /// @return Integral value corresponding to `pinkytoe::Player` enumeration
  inline constexpr std::int8_t next_player() const noexcept
  {
    return calculate_turn(this->p1_, this->count_);
  }
};

/// @brief Retrieves move position from the top of the stack
/// @param r Stores row index from the top of the stack
/// @param c Stores column index from the top of the stack
constexpr void
MoveHistory::top(std::uint8_t& r, std::uint8_t& c) const noexcept
{
  std::uint8_t stack_pos = this->count_ - 1;
  std::uint8_t byte_index = stack_pos >> 1;
  std::uint8_t shift = (stack_pos & 1) << 2;
  std::uint8_t frame_index = (this->data_[byte_index] >> shift) & 15;
  index_to_rc(frame_index, r, c);
}

/// @brief Adds next move to history
/// @param r Row index
/// @param c Column index
constexpr void
MoveHistory::push(std::uint8_t r, std::uint8_t c) noexcept
{
  std::uint8_t frame_index = rc_to_index(r, c);
  std::uint8_t byte_index = this->count_ >> 1;
  std::uint8_t shift = (this->count_ & 1) << 2;
  this->data_[byte_index] &= ~0u >> shift;
  this->data_[byte_index] |= frame_index << shift;
  ++this->count_;
}

/// @brief Removes last move from history
/// @param r Stores popped row index
/// @param c Stores popped column index
constexpr void
MoveHistory::pop(std::uint8_t& r, std::uint8_t& c) noexcept
{
  --this->count_;
  std::uint8_t byte_index = this->count_ >> 1;
  std::uint8_t shift = (this->count_ & 1) << 2;
  std::uint8_t frame_pos = (this->data_[byte_index] >> shift) & 15;
  index_to_rc(frame_pos, r, c);
}

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_MOVE_HISTORY_HPP_
