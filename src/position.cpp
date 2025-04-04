#include "position.h"

namespace pinkytoe::impl
{
/// @brief 
/// @param r 
/// @param c 
/// @return 
constexpr std::uint8_t position_to_index(std::uint8_t r, std::uint8_t c) noexcept
{
  return r * 3 + c;
}

/// @brief 
/// @param i 
/// @param r 
/// @param c 
constexpr void index_to_position(std::uint8_t i, std::uint8_t& r, std::uint8_t& c) noexcept
{
  r = i / 3;
  c = i % 3;
}

} // namespace pinkytoe::impl
