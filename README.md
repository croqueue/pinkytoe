![libpinkytoe](https://github.com/islandu/pinkytoe/blob/main/.github/images/mascot.png)

# libpinkytoe
_Note: This library is pre-release and is not stable_  
A simple and portable Tic-Tac-Toe implementation (C++17). This library is intended to be equally usable by C++ programmers working in userland or bare-metal.

## Purpose
`libpinkytoe` serves the following functions:
- As a pedagogical example for those just getting their feet wet with _modern_ C++ (metaprogramming, while indeed fabulous/powerful, is not a major focus here)
- As an example of memory safety in C++ (this is more about the build system)
- As a place for C++ enthusiasts of all experience levels to form community around simple game engines that are fun to build.

Once I stabilize the library, I encourage anyone in the FOSS community to fork me and create examples of `libpinkytoe`'s usage in a wide variety of contexts (e.g., a graphic or terminal-based Tic-Tac-Toe game, or firmware for a RaspberryPi Pico with peripherals that handle the controller and view).

## Dependencies
`libpinkytoe` depends upon the following headers from the C++ standard library:
- `cstddef`
- `cstdint`

Regardless of the target of your Tic-Tac-Toe application, `libpinkytoe` is easily portable because it only requires a C++17 compiler to build.

## Installation
CMake is the only current build option for `libpinkytoe`.

## Test Suite
The `libpinkytoe` test suite is built upon the GoogleTest framework.
