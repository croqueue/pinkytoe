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
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_link_libraries(frame_tests
  GTest::gtest_main
)

gtest_discover_tests(frame_tests)

# MetaTests

add_executable(
  meta_tests
  meta_tests.cpp
)

target_include_directories(meta_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_link_libraries(meta_tests
  pinkytoe
  GTest::gtest_main
)

gtest_discover_tests(meta_tests)

# MoveHistoryTests

add_executable(
  move_history_tests
  move_history_tests.cpp
)

target_include_directories(move_history_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_link_libraries(move_history_tests
  pinkytoe
  GTest::gtest_main
)

gtest_discover_tests(move_history_tests)

# MoveLedgerTests

add_executable(
  move_ledger_tests
  move_ledger_tests.cpp
)

target_include_directories(move_ledger_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_link_libraries(move_ledger_tests
  pinkytoe
  GTest::gtest_main
)

gtest_discover_tests(move_ledger_tests)

# PlayerTests

add_executable(
  player_tests
  player_tests.cpp
)

target_include_directories(player_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_link_libraries(player_tests
  pinkytoe
  GTest::gtest_main
)

gtest_discover_tests(player_tests)

# PositionTests

add_executable(
  position_tests
  position_tests.cpp
)

target_include_directories(position_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_link_libraries(position_tests
  pinkytoe
  GTest::gtest_main
)

gtest_discover_tests(position_tests)
