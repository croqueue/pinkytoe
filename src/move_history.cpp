#include "pinkytoe/move_history.h"
#include "position.h"

namespace pinkytoe
{

constexpr void MoveHistory::push_back(std::uint8_t r, std::uint8_t c) noexcept
{
  using impl::position_to_index;

  std::uint8_t matrix_pos = position_to_index(r, c);
  std::uint8_t byte_index = this->count_ >> 1;
  auto shift = (this->count_ & 1) << 2;
  this->data_[byte_index] &= ~0u >> shift;
  this->data_[byte_index] |= matrix_pos << shift;
  ++this->count_;
}

constexpr void MoveHistory::pop_back() noexcept
{
  --this->count_;
}

constexpr void MoveHistory::pop_back(std::uint8_t& r, std::uint8_t& c) noexcept
{
  --this->count_;
  std::uint8_t byte_index = this->count_ >> 1;
  auto shift = (this->count_ & 1) << 2;
  std::uint8_t matrix_pos = (this->data_[byte_index] >> shift) & 15;
  r = matrix_pos / 3;
  c = matrix_pos % 3;
}

constexpr std::uint8_t MoveHistory::move_count() const noexcept
{
  return this->count_;
}

} // namespace pinkytoe
