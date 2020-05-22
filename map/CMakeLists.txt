
add_executable(map_efficient_insert efficient_insert.cpp)
target_link_libraries(map_efficient_insert PRIVATE doctest)
add_test(NAME "map::efficient-insert" COMMAND map_efficient_insert)
