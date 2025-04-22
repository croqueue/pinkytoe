cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52204f78f94d7512df1f0f3bea1d47437a2c3a58.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# FrameTests

add_executable(
  frame_tests
  frame_tests.cpp
)

target_include_directories(frame_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(frame_tests
  GTest::gtest_main
)

gtest_discover_tests(frame_tests)

# MoveHistoryTests

add_executable(
  move_history_tests
  move_history_tests.cpp
)

target_include_directories(move_history_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(move_history_tests
  pinkytoe
  GTest::gtest_main
)

gtest_discover_tests(move_history_tests)

# ScoreLedgerTests

add_executable(
  score_ledger_tests
  score_ledger_tests.cpp
)

target_include_directories(score_ledger_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(score_ledger_tests
  pinkytoe
  GTest::gtest_main
)

gtest_discover_tests(score_ledger_tests)

# BasicToeTests

add_executable(
  basic_toe_tests
  basic_toe_tests.cpp
)

target_include_directories(basic_toe_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(basic_toe_tests
  pinkytoe
  GTest::gtest_main
)

gtest_discover_tests(basic_toe_tests)
