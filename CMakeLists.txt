cmake_minimum_required(VERSION 3.8)
project(CxxAlgorithms)

set(CMAKE_CXX_STANDARD 14)

include(tinyCUnit/tinyCUnit.cmake)

add_subdirectory(arithmetics)
add_subdirectory(casting)
add_subdirectory(encoding)
add_subdirectory(hashing)
add_subdirectory(random)
add_subdirectory(semantics)
add_subdirectory(stl)
