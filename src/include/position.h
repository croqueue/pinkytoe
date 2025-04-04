#ifndef PINKYTOE_IMPL_POSITION_H_
#define PINKYTOE_IMPL_POSITION_H_

#include <cstdint>

namespace pinkytoe::impl
{

/// @brief Converts row/column to flat matrix index
/// @param r Row index
/// @param c Column index
/// @return Corresponding index in flat matrix
inline constexpr std::uint8_t position_to_index(std::uint8_t r, std::uint8_t c) noexcept;

/// @brief Converts flat matrix index to row/column
/// @param i Index in matrix
/// @param r Mutable reference to store the row
/// @param c Mutable reference to store the column
inline constexpr void index_to_position(std::uint8_t i, std::uint8_t& r, std::uint8_t& c) noexcept;

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_POSITION_H_
