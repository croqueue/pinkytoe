#ifndef LIBT3_ENUMS_HPP_
#define LIBT3_ENUMS_HPP_

#include <cstdint>

namespace libt3
{

/// @brief Enumeration of players
enum class Player : std::int8_t
{
  /// @brief Indicates cell is owned by player O
  O = -1,
  /// @brief Indicates cell is vacant
  None = 0,
  /// @brief Indicates cell is owned by player X
  X = 1,
  /// @brief Indicates error in retrieving player
  Error = 127
};

/// @brief Enumeration of rows on the board
enum class Row : uint8_t
{
  /// @brief 
  Top     = 0,
  /// @brief 
  Middle  = 1,
  /// @brief 
  Bottom  = 2
};

/// @brief Enumeration of columns on the board
enum class Column : uint8_t
{
  /// @brief 
  Left    = 0,
  /// @brief 
  Middle  = 1,
  /// @brief 
  Right   = 2
};

/// @brief Enumeration of possible move outcomes
enum class Status : int
{
  /// @brief Indicates successful move
  Ok = 0,
  /// @brief Result of the move is Player X winning the game
  PlayerXWins = 1,
  /// @brief Result of the move is Player O winning the game
  PlayerOWins = 2,
  /// @brief Indicates the cell is already occupied
  CellOccupied = -1,
  /// @brief Indicates invalid row/column arguments
  RangeError = -2,
  /// @brief Indicates game has ended
  GameHasEnded = -3,
  /// @brief Move attempted without starting player selected
  PlayerNotSelected = -4,
  /// @brief 
  CantUndo = -5
};

} // namespace libt3

#endif // !LIBT3_ENUMS_HPP_
