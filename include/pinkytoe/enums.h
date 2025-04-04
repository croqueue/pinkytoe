#ifndef PINKYTOE_ENUMS_H_
#define PINKYTOE_ENUMS_H_

#include <cstdint>

namespace pinkytoe
{

/// @brief Enumeration of players
enum class Player : std::int8_t {
  X     = -1,
  None  = 0,
  O     = 1
};

/// @brief Enumeration of rows on the board
enum class Row : std::uint8_t {
  Top     = 0,
  Middle  = 1,
  Bottom  = 2
};

/// @brief Enumeration of columns on the board
enum class Column : std::uint8_t {
  Left    = 0,
  Middle  = 1,
  Right   = 2
};

} // namespace pinkytoe

#endif // !PINKYTOE_ENUMS_H_
