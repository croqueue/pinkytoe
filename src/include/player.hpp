#ifndef PINKYTOE_IMPL_PLAYER_HPP_
#define PINKYTOE_IMPL_PLAYER_HPP_

#include <cstdint>

#include "meta.hpp"
#include "pinkytoe/enums.h"

namespace pinkytoe::impl {

/// PROTOTYPES

/// @brief Whose turn is it anyway
/// @param player1 The player that played first (enumeration)
/// @param n Number of turns that have been taken
/// @return Player who goes next (enumeration)
inline constexpr Player
whose_turn(Player player1, std::uint8_t n) noexcept;

/// @brief Whose turn is it anyway
/// @param player1 The player that started the game (integral)
/// @param n Number of turns that have been taken
/// @return Player who goes next (integral)
inline constexpr std::int8_t
whose_turn(std::int8_t player1, std::uint8_t n) noexcept;

/// @brief Toggles between `Player::X` and `Player::O`
/// @param player Input player (enumeration)
/// @return The opposing player to `player` (enumeration)
inline constexpr Player
flip_player(Player player) noexcept;

/// @brief Toggles between integral casts of `Player::X` and `Player::O`
/// @param player Input player (integral)
/// @return The opposing player to `player` (integral)
inline constexpr std::int8_t
flip_player(std::int8_t player) noexcept;

/// IMPLEMENTATIONS

/// @brief Whose turn is it anyway
/// @param player1 The player that started the game (enumeration)
/// @param n Number of turns that have been taken
/// @return Player who goes next (enumeration)
constexpr Player
whose_turn(Player player1, std::uint8_t n) noexcept
{
  auto p1 = enum_as_integral(player1);
  auto p_n = whose_turn(p1, n);
  return static_cast<Player>(p_n);
}

/// @brief Whose turn is it anyway
/// @param player1 The player that started the game (integral)
/// @param n Number of turns that have been taken
/// @return Player who goes next (integral)
constexpr std::int8_t
whose_turn(std::int8_t player1, std::uint8_t n) noexcept
{
  auto flip = static_cast<std::int8_t>(n & 1);
  auto p1_mul = 1 - (flip << 1);
  return player1 * p1_mul;
}

/// @brief Toggles between `Player::X` and `Player::O`
/// @param player Input player (enumeration)
/// @return The opposing player to `player` (enumeration)
constexpr Player
flip_player(Player player) noexcept
{
  // Player::None is noop
  auto p = enum_as_integral(player);
  return static_cast<Player>(p * -1);
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
