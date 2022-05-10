# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Name of the project
project(GomoTux3)

file(GLOB_RECURSE SRC "src/*.cpp")
add_executable(gomoku ${SRC})