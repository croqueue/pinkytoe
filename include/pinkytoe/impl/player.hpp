#ifndef PINKYTOE_IMPL_PLAYER_HPP_
#define PINKYTOE_IMPL_PLAYER_HPP_

#include <cstdint>

#include "pinkytoe/impl/enums.hpp"
#include "pinkytoe/impl/player.hpp"

namespace pinkytoe::impl {

/// [PROTO] ///

/// @brief Whose turn is it anyway
/// @param p1 The player that started the game (integral)
/// @param n Number of turns that have been taken
/// @return Player who goes next (integral)
inline constexpr std::int8_t
calculate_turn(std::int8_t p1, std::uint8_t n) noexcept;

/// @brief Toggles between integral casts of `Player::X` and `Player::O`
/// @param player Input player (integral)
/// @return The opposing player to `player` (integral)
inline constexpr std::int8_t
flip_player(std::int8_t player) noexcept;

/// [IMPL] ///

/// @brief Whose turn is it anyway
/// @param p1 The player that started the game (integral)
/// @param n Number of turns that have been taken
/// @return Player who goes next (integral)
constexpr std::int8_t
calculate_turn(std::int8_t p1, std::uint8_t n) noexcept
{
  std::int8_t mul[2] = { 1, -1 };
  return p1 * mul[n & 1];
}

/// @brief Toggles between integral casts of `Player::X` and `Player::O`
/// @param player Input player (integral)
/// @return The opposing player to `player` (integral)
constexpr std::int8_t
flip_player(std::int8_t player) noexcept
{
  return player * -1;
}

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_PLAYER_HPP_
