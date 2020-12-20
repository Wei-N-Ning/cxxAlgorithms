
add_executable(set_union union.cpp)
target_link_libraries(set_union PRIVATE doctest)
add_test(NAME "set::union" COMMAND set_union)

add_executable(set_boost_flat_set boost_flat_set.cpp)
target_include_directories(set_boost_flat_set PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(set_boost_flat_set PRIVATE doctest)
add_test(NAME "set::boost-flat-set" COMMAND set_boost_flat_set)

add_executable(set_extract_insert extract_insert.cpp)
target_link_libraries(set_extract_insert PRIVATE doctest)
add_test(NAME "set::extract_insert" COMMAND set_extract_insert)
