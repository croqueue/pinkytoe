add_executable(basic_term src/main.cpp)
target_include_directories(basic_term
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
