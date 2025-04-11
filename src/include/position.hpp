#ifndef PINKYTOE_IMPL_POSITION_HPP_
#define PINKYTOE_IMPL_POSITION_HPP_

#include <cstdint>

#include "meta.hpp"
#include "pinkytoe/enums.h"

namespace pinkytoe::impl {

/// PROTOTYPES

/// @brief Converts row/column to flat matrix index
/// @param r Row index
/// @param c Column index
/// @return Corresponding index in flat matrix
inline constexpr std::uint8_t
rc_to_index(std::uint8_t r, std::uint8_t c) noexcept;

/// @brief Converts flat matrix index to row/column
/// @param i Index in matrix
/// @param r Mutable reference to store the row
/// @param c Mutable reference to store the column
inline constexpr void
index_to_rc(std::uint8_t i, std::uint8_t& r, std::uint8_t& c) noexcept;

/// @brief Validates row and column enumerations
/// @param row Row enumeration
/// @param column Column enumeration
/// @return `true` if position is on the board, else `false`
inline constexpr bool
position_valid(Row row, Column column) noexcept;

/// IMPLEMENTATIONS

/// @brief Converts row/column to flat matrix index
/// @param r Row index
/// @param c Column index
/// @return Corresponding index in flat matrix
constexpr std::uint8_t
rc_to_index(std::uint8_t r, std::uint8_t c) noexcept
{
  return r * 3 + c;
}

/// @brief Converts flat matrix index to row/column
/// @param i Index in matrix
/// @param r Mutable reference to store the row
/// @param c Mutable reference to store the column
constexpr void
index_to_rc(std::uint8_t i, std::uint8_t& r, std::uint8_t& c) noexcept
{
  r = i / 3;
  c = i % 3;
}

/// @brief Validates row and column enumerations
/// @param row Row enumeration
/// @param column Column enumeration
/// @return `true` if position is on the board, else `false`
constexpr bool
position_valid(Row row, Column column) noexcept
{
  auto r = enum_as_integral(row);
  auto c = enum_as_integral(column);
  return r <= 2 && c <= 2;
}

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_POSITION_HPP_
