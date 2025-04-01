#include <cstddef>
#include "pinkytoe/enums.h"
#include "meta.hpp"
#include "player.h"

namespace pinkytoe::impl
{

/// @brief 
/// @param start_player 
/// @param move_count 
/// @return 
constexpr Player current_player(Player start_player, std::uint8_t move_count) noexcept
{
  auto is_player_2 = move_count & 2;
  return is_player_2 ? flip_player(start_player) : start_player;
}

/// @brief 
/// @param player 
/// @return 
constexpr Player flip_player(Player player) noexcept
{
  auto p = enum_as_integral(player);
  return static_cast<Player>(p * -1);
}

} // namespace pinkytoe::impl
