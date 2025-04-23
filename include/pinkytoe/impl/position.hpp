#ifndef PINKYTOE_IMPL_POSITION_HPP_
#define PINKYTOE_IMPL_POSITION_HPP_

#include <cstdint>

#include "pinkytoe/impl/enums.hpp"
#include "pinkytoe/impl/meta.hpp"

namespace pinkytoe::impl {

/// PROTO

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

/// @brief Converts flat matrix index to row/column
/// @param i Index in matrix
/// @param row Mutable reference to store the row enumeration
/// @param column Mutable reference to store the column enumeration
inline constexpr void
index_to_rc(std::uint8_t i, Row& r, Column& c) noexcept;

/// @brief Validates row and column enumerations
/// @param r Row enumeration
/// @param c Column enumeration
/// @return `true` if position is on the board, else `false`
inline constexpr bool
position_valid(std::uint8_t r, std::uint8_t c) noexcept;

/// IMPL

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

/// @brief Converts flat matrix index to row/column
/// @param i Index in matrix
/// @param row Mutable reference to store the row enumeration
/// @param column Mutable reference to store the column enumeration
inline constexpr void
index_to_rc(std::uint8_t i, Row& row, Column& column) noexcept
{
  row = static_cast<Row>(i / 3);
  column = static_cast<Column>(i % 3);
}

/// @brief Validates row and column enumerations
/// @param r Row enumeration
/// @param c Column enumeration
/// @return `true` if position is on the board, else `false`
constexpr bool
position_valid(std::uint8_t r, std::uint8_t c) noexcept
{
  return r <= 2 && c <= 2;
}

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_POSITION_HPP_
