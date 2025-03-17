# libt3-cpp
A pedagogical example of a C++ header-only library that provides a simple and portable Tic-Tac-Toe game engine (C++17)

# Installation
This is a header-only library, so the only installation method is to simply copy `include/libt3` from this repository into your project's include directory.

# API/Usage
`libt3::TicTacToe` provides an API for implementing your own Tic-Tac-Toe application in C++. It has a single constructor, the usage of which is shown below:

## Constructor
```cpp
#include "libt3/enums.hpp"
#include "libt3/game.hpp"

using libt3::Player;
using libt3::TicTacToe;

auto starting_player = Player::X; // or Player::O
TicTacToeBoard board(starting_player);
```

## Placement
To place `X` or `O` on the board, simply call the `place_next` method. The following code places `starting_player` in the middle square.

```cpp
using libt3::Column;
using libt3::Row;

board.place_next(Row::Middle, Column::Middle);
``` 

The return value specifies the result of the placement, which is enumerated by the `libt3::MoveResult` type.

```cpp
using libt3::Status;

Status status = board.place_next(Row::Bottom, Column::Left);
```

## Move Results
The result of each placement of an `X` or an `O` on the board can be evaluated as follows:

```cpp
switch (result) {
case Status::Ok:
    // Indicates valid placement
    break;
case Status::PlayerXWins:
    // Indicates valid placement (`CellOwner::PlayerX` wins)
    break;
case Status::PlayerOWins:
    // Indicates valid placement (`CellOwner::PlayerO` wins)
    break;
case Status::CellOccupied:
    // Indicates the requested cell is already claimed
    break;
case Status::RangeError:
    // Indicates invalid row and/or column
    break;
case Status::GameIsOver:
    // Indicates placement attempt after game has ended
    break;
default:
    // 🤷
    break;
}
```
