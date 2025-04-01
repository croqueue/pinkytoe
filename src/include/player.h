#include <cstdint>
#include "pinkytoe/enums.h"


namespace pinkytoe::impl
{

/// @brief 
/// @param start_player 
/// @param move_count 
/// @return 
inline constexpr Player current_player(Player start_player, std::uint8_t move_count) noexcept;

/// @brief 
/// @param player 
/// @return 
inline constexpr Player flip_player(Player player) noexcept;

} // namespace pinkytoe::impl
