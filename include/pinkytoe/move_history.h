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

  /// @brief 
  /// @param r 
  /// @param c 
  inline constexpr void push_back(std::uint8_t r, std::uint8_t c) noexcept;

  /// @brief 
  inline constexpr void pop_back() noexcept;

  /// @brief 
  /// @param r 
  /// @param c 
  inline constexpr void pop_back(std::uint8_t& r, std::uint8_t& c) noexcept;

  /// @brief 
  /// @return 
  inline constexpr std::uint8_t move_count() const noexcept;
};

} // namespace pinkytoe

#endif // !PINKYTOE_MOVE_HISTORY_H_
