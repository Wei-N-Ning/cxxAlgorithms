cmake_minimum_required(VERSION 3.8)
project(C++STL-Algorithms)

enable_testing()
find_program(BASH_PROGRAM bash)
include(tinyCUnit/tinyCUnit.cmake)

add_subdirectory(arithmetics)
add_subdirectory(casting)
add_subdirectory(encoding)
add_subdirectory(hashing)
add_subdirectory(random)
add_subdirectory(stl)