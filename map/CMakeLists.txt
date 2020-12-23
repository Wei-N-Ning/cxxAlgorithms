
add_executable(map_efficient_insert efficient_insert.cpp)
target_link_libraries(map_efficient_insert PRIVATE doctest)
add_test(NAME "map::efficient-insert" COMMAND map_efficient_insert)

add_executable(map_efficient_accessing efficient_map_accessing.cpp)
target_link_libraries(map_efficient_accessing PRIVATE doctest)
add_test(NAME "map::efficient_accessing" COMMAND map_efficient_accessing)

add_executable(map_adhoc_sort_function adhoc_sort_function.cpp)
target_link_libraries(map_adhoc_sort_function PRIVATE doctest)
add_test(NAME "map::adhoc_sort_function" COMMAND map_adhoc_sort_function)

add_executable(map_extract_insert extract_insert.cpp)
target_link_libraries(map_extract_insert PRIVATE doctest)
add_test(NAME "map::extract_insert" COMMAND map_extract_insert)
