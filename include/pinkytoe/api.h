#ifndef PINKYTOE_API_H_
#define PINKYTOE_API_H_

#include "pinkytoe/impl/basic_toe.hpp"
#include "pinkytoe/impl/enums.hpp"
#include "pinkytoe/impl/ultimate_toe.hpp"

namespace pinkytoe {

/// impl/basic_toe.hpp
using TicTacToe = impl::BasicToe;

/// impl/enums.hpp
using impl::Column;
using impl::MoveResult;
using impl::Player;
using impl::Row;

/// impl/ultimate_toe.hpp
using UltimateTicTacToe = impl::UltimateToe;

} // namespace pinkytoe

#endif // !PINKYTOE_API_H_
