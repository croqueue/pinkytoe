#pragma once

#include "pinkytoe/impl/basic_toe.hpp"
#include "pinkytoe/impl/enums.hpp"
#include "pinkytoe/impl/frame.hpp"
#include "pinkytoe/impl/meta.hpp"
#include <array>

namespace pinkytoe::impl {

using BasicToeMatrix = std::array<std::array<BasicToe, 3>, 3>;

class UltimateToe final
{
  BasicToeMatrix gmatrix_;
  std::uint8_t r_, c_;
  Frame uframe_;

public:
  inline constexpr UltimateToe(Player first_player,
                               Row row,
                               Column column) noexcept
    : gmatrix_{}
    , r_(enum_as_integral(row))
    , c_(enum_as_integral(column))
    , uframe_{}
  {
    this->gmatrix_[this->r_][this->c_] = BasicToe(first_player);
  }
};

} // namespace pinkytoe::impl
