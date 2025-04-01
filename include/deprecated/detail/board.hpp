#ifndef LIBT3_DETAIL_BOARD_HPP_
#define LIBT3_DETAIL_BOARD_HPP_

#include <cstdint>
#include "libt3/enums.hpp"
#include "libt3/detail/common.hpp"

namespace libt3::detail
{

/// @brief 
class Board final {
  /// @brief 
  std::uint32_t data_ {};

public:

  /// @brief 
  /// @param row 
  /// @param column 
  /// @return 
  inline constexpr Player get(Row row, Column column) const noexcept
  {
    if (!validate_position(row, column))
      return Player::Error;
    
    auto r = enum_as_integral(row);
    auto c = enum_as_integral(column);

    auto start_bit = (r * 3 + c) << 1;
    auto bits = (this->data_ >> start_bit) & 3;
    std::int8_t sign_mul = bits >> 1 ? -1 : 1;
    std::int8_t p = static_cast<std::int8_t>(bits & 1) * sign_mul;
    return static_cast<Player>(p);
  }

  /// @brief 
  /// @param row 
  /// @param column 
  /// @param player 
  /// @return 
  inline constexpr Player set(Row row, Column column, Player player) noexcept
  {
    auto p = enum_as_integral(player);

    if (!validate_position(row, column) || p < -1 || p > 1)
      return Player::Error;
    
    auto r = enum_as_integral(row);
    auto c = enum_as_integral(column);

    // Clear current bits
    auto start_bit = (r * 3 + c) << 1;
    this->data_ &= ~(3u << start_bit);
    // Get sign bit
    std::uint8_t pbits = bool_as_integral(p < 0) << 1;
    // Add value bit
    pbits |= static_cast<std::uint8_t>(p) & 1;
    // Shift bits and combine
    this->data_ |= static_cast<std::uint32_t>(pbits) << start_bit;
    return player;
  }
};

} // namespace libt3::detail

#endif // !LIBT3_DETAIL_BOARD_HPP_
