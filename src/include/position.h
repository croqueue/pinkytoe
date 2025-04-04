#include <cstdint>

namespace pinkytoe::impl
{
/// @brief 
/// @param r 
/// @param c 
/// @return 
inline constexpr std::uint8_t position_to_index(std::uint8_t r, std::uint8_t c) noexcept;

/// @brief 
/// @param i 
/// @param r 
/// @param c 
inline constexpr void index_to_position(std::uint8_t i, std::uint8_t& r, std::uint8_t& c) noexcept;

} // namespace pinkytoe::impl
