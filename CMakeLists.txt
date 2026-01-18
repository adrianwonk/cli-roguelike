cmake_minimum_required(VERSION 3.21)

project(cli-game LANGUAGES CXX)

add_executable(main
  main.cpp
  Entity.cpp
)
target_compile_features(main PRIVATE cxx_std_20)

find_package(Curses REQUIRED)

target_link_libraries(main PRIVATE ${CURSES_LIBRARIES})
target_include_directories(main PRIVATE ${CURSES_INCLUDE_DIRS})
