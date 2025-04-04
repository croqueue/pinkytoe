#ifndef PINKYTOE_IMPL_FRAME_H_
#define PINKYTOE_IMPL_FRAME_H_

#include <cstdint>
#include "pinkytoe/enums.h"
#include "position.h"

namespace pinkytoe::impl
{

/// @brief A snapshot of the game
class Frame final {
  /// 9 pixels * 2 bits per pixel = 18 bits
  std::uint8_t data_[3];
public:
  Frame() = default;

  /// @brief Retrieves pixel value at position
  /// @param r Row index
  /// @param c Column index
  /// @return Current pixel value
  inline constexpr std::int8_t get_pixel(std::uint8_t r, std::uint8_t c) noexcept;

  /// @brief Sets pixel value at position
  /// @param r Row index
  /// @param c Column index
  /// @param p Pixel value to set
  inline constexpr void set_pixel(std::uint8_t r, std::uint8_t c, std::int8_t p) noexcept;
};

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_FRAME_H_
