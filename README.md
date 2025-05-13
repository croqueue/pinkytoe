![libpinkytoe](https://github.com/croqueue/pinkytoe/blob/main/.github/images/mascot.png)

# libpinkytoe
_Note: This library is pre-release and is not stable_  
A tiny and portable tic-tac-toe engine that is equally usable by game developers working in userland, kernel space, or on bare metal.

## Purpose
`libpinkytoe` serves the following functions:
- As a pedagogical example for those just getting their feet wet with modern C++ (template metaprogramming, while indeed fabulous/powerful, is not a major focus here)
- As an example of memory safety in C/C++ (this is more about the build system)
- As a place for C/C++ enthusiasts of all experience levels to form community around simple game engines that are fun to build

I encourage anyone in the FOSS community to fork me and create examples of `libpinkytoe`'s usage in a wide variety of contexts, e.g.,
- A GUI or terminal-based Tic-Tac-Toe game
- A firmware implementation of the game with peripheral hardware handling player controls and view options
- No wrong answers, go nuts!

## Dependencies
`libpinkytoe` depends upon the following headers from the C++ standard library:
- `array`
- `cstdint`
- `type_traits`

Regardless of the target of your tic-tac-toe-based game, `libpinkytoe` is easily portable because it only requires a minimal C++17 compiler to build and use it.

## Build/Install
CMake is the only current build option for `libpinkytoe`. After you clone this repository...
```bash
cd pinkytoe
cmake -S . -B build
cmake --build build
```

Then run the unit tests...

```bash
ctest --test-dir build/tests
```

## Test Suite
The `libpinkytoe` test suite is built upon the GoogleTest framework [https://github.com/google/googletest](https://github.com/google/googletest)


## TODOs
- Automate code formatting as part of the VCS workflow
