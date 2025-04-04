#include <cstdint>
#include "pinkytoe/enums.h"


namespace pinkytoe::impl
{

/// @brief Whose turn is it anyway
/// @param player1 The player that played first (enumeration)
/// @param n Number of turns that have been taken
/// @return Player who goes next (enumeration)
inline constexpr Player whose_turn(Player player1, std::uint8_t n) noexcept;

/// @brief Whose turn is it anyway
/// @param player1 The player that started the game (integral)
/// @param n Number of turns that have been taken
/// @return Player who goes next (integral)
inline constexpr std::int8_t whose_turn(std::int8_t player1, std::uint8_t n) noexcept;

/// @brief Toggles between `Player::X` and `Player::O`
/// @param player Input player (enumeration)
/// @return The opposing player to `player` (enumeration)
inline constexpr Player flip_player(Player player) noexcept;

/// @brief Toggles between integral casts of `Player::X` and `Player::O`
/// @param player Input player (integral)
/// @return The opposing player to `player` (integral)
inline constexpr std::int8_t flip_player(std::int8_t player) noexcept;

} // namespace pinkytoe::impl
