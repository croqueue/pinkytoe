#include <cstdint>

namespace pinkytoe
{

/// @brief 
enum class Player : std::int8_t {
  X     = -1,
  None  = 0,
  O     = 1
};

/// @brief 
enum class Row : std::uint8_t {
  Top     = 0,
  Middle  = 1,
  Bottom  = 2
};

/// @brief 
enum class Column : std::uint8_t {
  Left    = 0,
  Middle  = 1,
  Right   = 2
};

} // namespace pinkytoe
