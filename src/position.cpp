#include "position.h"

namespace pinkytoe::impl
{

/// @brief Converts row/column to flat matrix index
/// @param r Row index
/// @param c Column index
/// @return Corresponding index in flat matrix
constexpr std::uint8_t position_to_index(std::uint8_t r, std::uint8_t c) noexcept
{
  return r * 3 + c;
}

/// @brief Converts flat matrix index to row/column
/// @param i Index in matrix
/// @param r Mutable reference to store the row
/// @param c Mutable reference to store the column
constexpr void index_to_position(std::uint8_t i, std::uint8_t& r, std::uint8_t& c) noexcept
{
  r = i / 3;
  c = i % 3;
}

} // namespace pinkytoe::impl
