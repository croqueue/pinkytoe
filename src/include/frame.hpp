#ifndef PINKYTOE_IMPL_FRAME_H_
#define PINKYTOE_IMPL_FRAME_H_

#include <cstdint>

#include "pinkytoe/enums.h"
#include "position.hpp"

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
  inline constexpr std::int8_t get_pixel(std::uint8_t r, std::uint8_t c) noexcept
  {
    auto index = position_to_index(r, c);
    auto byte = index >> 2;
    auto shift = (index & 3u) << 1;
    std::uint8_t bits = (this->data_[byte] >> shift) & 3u;
    auto p = static_cast<std::int8_t>(bits) - 1;
    return p;
  }

  /// @brief Sets pixel value at position
  /// @param r Row index
  /// @param c Column index
  /// @param p Pixel value to set
  inline constexpr void set_pixel(std::uint8_t r, std::uint8_t c, std::int8_t p) noexcept
  {
    std::uint8_t bits = static_cast<std::uint8_t>(p + 1);
    auto index = position_to_index(r, c);
    auto byte = index >> 2;
    auto shift = (index & 3u) << 1;
    this->data_[byte] &= ~(3u << shift);
    this->data_[byte] |= bits << shift;
  }
};

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_FRAME_H_
