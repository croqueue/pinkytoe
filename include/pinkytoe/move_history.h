#ifndef PINKYTOE_MOVE_HISTORY_H_
#define PINKYTOE_MOVE_HISTORY_H_

#include <cstdint>

namespace pinkytoe
{

/// @brief Tracks player choices over the course of a game
class MoveHistory final {
  
  std::uint8_t data_[5];
  std::uint8_t count_;

public:
  MoveHistory() = default;

  /// @brief Retrieves move position from the top of the stack 
  /// @param r Stores row index from the top of the stack
  /// @param c Stores column index from the top of the stack
  inline constexpr void top(std::uint8_t& r, std::uint8_t& c) const noexcept;

  /// @brief Adds next move to history 
  /// @param r Row index
  /// @param c Column index
  inline constexpr void push(std::uint8_t r, std::uint8_t c) noexcept;

  /// @brief Removes last move from history
  inline constexpr void pop() noexcept;

  /// @brief Removes last move from history
  /// @param r Stores popped row index
  /// @param c Stores popped column index
  inline constexpr void pop(std::uint8_t& r, std::uint8_t& c) noexcept;

  /// @brief Returns number of moves currently recorded
  /// @return Number of recorded moves
  inline constexpr std::uint8_t move_count() const noexcept;
};

} // namespace pinkytoe

#endif // !PINKYTOE_MOVE_HISTORY_H_
