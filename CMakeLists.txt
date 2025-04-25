cmake_minimum_required(VERSION 3.14)

project(pinkytoe
        VERSION 0.1
        DESCRIPTION "A simple and portable TicTacToe engine"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build the unit tests" OFF)
option(BUILD_EXAMPLES "Build the usage examples" OFF)

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(pinkytoe STATIC include/pinkytoe/api.h)

set_source_files_properties(
  include/pinkytoe/api.h
  PROPERTIES
  LANGUAGE CXX
)

# target_sources(pinkytoe PRIVATE include/pinkytoe/api.h)

target_include_directories(pinkytoe
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(pinkytoe PROPERTIES VERSION ${PROJECT_VERSION})

target_compile_options(pinkytoe PUBLIC -Wall -Werror -Wextra -pedantic)
