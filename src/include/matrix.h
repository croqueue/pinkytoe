#include <cstdint>
#include "pinkytoe/enums.h"
#include "position.h"

namespace pinkytoe::impl
{

class Matrix final {
  // 2bits * 9 cells = 18 bits
  std::uint8_t data_[3];
public:
  Matrix() = default;

  /// @brief 
  /// @param r 
  /// @param c 
  /// @return 
  inline constexpr std::int8_t get(std::uint8_t r, std::uint8_t c) noexcept;

  /// @brief 
  /// @param r 
  /// @param c 
  /// @param p 
  inline constexpr void set(std::uint8_t r, std::uint8_t c, std::int8_t p) noexcept;
};

} // namespace pinkytoe::impl
