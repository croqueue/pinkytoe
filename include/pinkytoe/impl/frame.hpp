#ifndef PINKYTOE_IMPL_FRAME_HPP_
#define PINKYTOE_IMPL_FRAME_HPP_

#include <cstdint>

#include "pinkytoe/impl/position.hpp"

namespace pinkytoe::impl {

/// @brief A snapshot of the game board
class Frame final
{
  std::uint8_t data_[3]; // 9 squares * 2 bits per square = 18 bits required

public:
  /// @brief Initializes empty frame
  inline constexpr Frame() noexcept
    : data_{ 0x55, 0x55, 0x01 }
  {
  }

  /// @brief Retrieves square value at position
  /// @param r Row index
  /// @param c Column index
  /// @return Current square value
  inline constexpr std::int8_t get_square(std::uint8_t r,
                                          std::uint8_t c) const noexcept
  {
    /// Calculate storage location of the bits
    std::uint8_t index = rc_to_index(r, c);
    std::uint8_t byte = index >> 2;
    std::uint8_t shift = (index & 3u) << 1;
    /// Extract bits and convert to value
    std::uint8_t bits = (this->data_[byte] >> shift) & 3u;
    auto p = static_cast<std::int8_t>(bits) - 1;
    return p;
  }

  /// @brief Sets square value at position
  /// @param r Row index
  /// @param c Column index
  /// @param p square value to set
  inline constexpr void set_square(std::uint8_t r,
                                   std::uint8_t c,
                                   std::int8_t p) noexcept
  {
    /// Convert value to unsigned bits
    std::uint8_t bits = static_cast<std::uint8_t>(p + 1);
    /// Calculate storage location of the bits
    std::uint8_t index = rc_to_index(r, c);
    std::uint8_t byte = index >> 2;
    std::uint8_t shift = (index & 3u) << 1;
    /// Clear bits and combine
    this->data_[byte] &= ~(3u << shift);
    this->data_[byte] |= bits << shift;
  }
};

} // namespace pinkytoe::impl

#endif // !PINKYTOE_IMPL_FRAME_HPP_
