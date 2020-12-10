cmake_minimum_required(VERSION 3.12)

# avoid this
# see: https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#how-do-i-use-a-different-compiler
# and: 
# https://stackoverflow.com/questions/13054451/unable-to-specify-the-compiler-with-cmake
# https://stackoverflow.com/questions/11588855/how-do-you-set-cmake-c-compiler-and-cmake-cxx-compiler-for-building-assimp-for-i
set(CMAKE_C_COMPILER gcc-9)
set(CMAKE_CXX_COMPILER g++-9)

project(CxxAlgorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_USE_STATIC_LIBS TRUE)
set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/vendor/boost-1.72.0)
find_package(Boost 1.72.0 REQUIRED COMPONENTS regex timer)

enable_testing()
add_subdirectory(vendor/doctest)

add_subdirectory(arithmetics)
add_subdirectory(casting)
add_subdirectory(encoding)
add_subdirectory(hashing)
add_subdirectory(remove)
add_subdirectory(random)
add_subdirectory(semantics)
add_subdirectory(stl)
add_subdirectory(graph)
add_subdirectory(iteration)
add_subdirectory(memoization)
add_subdirectory(insert)
add_subdirectory(ordered)
add_subdirectory(partition)
add_subdirectory(search)
add_subdirectory(fractal)
add_subdirectory(set)
add_subdirectory(map)
add_subdirectory(tree)
add_subdirectory(prefix)
add_subdirectory(dp)