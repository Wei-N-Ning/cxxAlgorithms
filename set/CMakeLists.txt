
add_executable(set_union union.cpp)
target_link_libraries(set_union PRIVATE doctest)
add_test(NAME "set::union" COMMAND set_union)
