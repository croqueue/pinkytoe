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
  XWinsHorizontal1,
  XWinsHorizontal2,
  XWinsHorizontal3,
  XWinsVertical1,
  XWinsVertical2,
  XWinsVertical3,
  XWinsDiagonal,
  XWinsAntidiagonal,
  OWinsHorizontal1,
  OWinsHorizontal2,
  OWinsHorizontal3,
  OWinsVertical1,
  OWinsVertical2,
  OWinsVertical3,
  OWinsDiagonal,
  OWinsAntidiagonal,
  InvalidPosition = 252,
  SquareOccupied = 253,
  GameIsOver = 254,
  CannotUndo = 255
};

} // namespace pinkytoe::impl
