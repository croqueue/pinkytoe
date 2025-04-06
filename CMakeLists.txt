cmake_minimum_required(VERSION 3.14)

project(pinkytoe
        VERSION 0.1
        DESCRIPTION "A simple and portable TicTacToe engine"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(tests)

file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(pinkytoe STATIC ${SRC_FILES})

target_include_directories(pinkytoe
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  # PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

set_target_properties(pinkytoe PROPERTIES VERSION ${PROJECT_VERSION})

target_compile_options(pinkytoe PUBLIC -Wall -Werror -Wextra -pedantic)
