#include <cstdint>
#include "matrix.h"
#include "position.h"

namespace pinkytoe::impl
{

constexpr std::int8_t Matrix::get(std::uint8_t r, std::uint8_t c) noexcept
{
  auto index = position_to_index(r, c);
  auto byte = index >> 2;
  auto shift = (index & 3u) << 1;
  std::uint8_t bits = (this->data_[byte] >> shift) & 3u;
  auto p = static_cast<std::int8_t>(bits) - 1;
  return p;
}

constexpr void Matrix::set(std::uint8_t r, std::uint8_t c, std::int8_t p) noexcept
{
  std::uint8_t bits = static_cast<std::uint8_t>(p + 1);
  auto index = position_to_index(r, c);
  auto byte = index >> 2;
  auto shift = (index & 3u) << 1;
  this->data_[byte] &= ~(3u << shift);
  this->data_[byte] |= bits << shift;
}

} // namespace pinkytoe::impl
