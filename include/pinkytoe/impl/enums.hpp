#pragma once

#include <cstdint>

namespace pinkytoe::impl {

/// @brief Enumeration of players
enum class Player : std::int8_t
{
  X = -1,
  None = 0,
  O = 1
};

/// @brief Enumeration of rows on the board
enum class Row : std::uint8_t
{
  Top = 0,
  Middle = 1,
  Bottom = 2
};

/// @brief Enumeration of columns on the board
enum class Column : std::uint8_t
{
  Left = 0,
  Middle = 1,
  Right = 2
};

/// @brief
enum class MoveResult : std::uint8_t
{
  Ok = 0,
  XWins = 1,
  OWins = 2,
  InvalidPosition = 3,
  SquareOccupied = 4,
  GameIsOver = 5,
  CannotUndo = 6
};

} // namespace pinkytoe::impl
