# libt3-cpp
A C++ header-only library that provides a simple and portable Tic-Tac-Toe game engine.

# Installation
Since this library consists of a single header file, installing the library for use in your project can easily be done in one of the two following ways:

## Option 1: Make this repository a submodule
See the git submodule documentation here: [Git SubModule Documentation](https://git-scm.com/docs/git-submodule).

## Option 2: `include/libt3.hpp`
Simply copy the header file into your project's source tree.

# API/Usage
`libt3::TicTacToeBoard` provides an API for implementing your own Tic-Tac-Toe application in C++. It has a single constructor, the usage of which is shown below:

## Constructor
```cpp
using libt3::TicTacToeBoard;
using libt3::CellOwner;

auto starting_player = CellOwner::PlayerX; // or CellOwner::PlayerO
TicTacToeBoard board(starting_player);
```

## Placement
To place `X` or `O` on the board, simply call the `place_next` method. The following code places `starting_player` in the middle square.

```cpp
board.place_next(1, 1);
``` 

The return value specifies the result of the placement, which is enumerated by the `libt3::MoveResult` type.

```cpp
using libt3::MoveResult;

MoveResult result = board.place_next(2, 0);
```

## Move Results
The result of each placement of an `X` or an `O` on the board can be evaluated as follows:

```cpp
switch (result) {
case MoveResult::Ok:
    // Indicates valid placement
    break;
case MoveResult::PlayerXWins:
    // Indicates valid placement (`CellOwner::PlayerX` wins)
    break;
case MoveResult::PlayerOWins:
    // Indicates valid placement (`CellOwner::PlayerO` wins)
    break;
case MoveResult::CellOccupied:
    // Indicates the requested cell is already claimed
    break;
case MoveResult::RangeError:
    // Indicates invalid row and/or column
    break;
case MoveResult::GameIsOver:
    // Indicates placement attempt after game has ended
    break;
default:
    // 🤷
    break;
}
```
