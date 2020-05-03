
add_executable(insert_vec_insert_elements vec_insert_elements.cpp)
target_link_libraries(insert_vec_insert_elements PRIVATE doctest)
add_test(NAME "insert::vector-insert-elements" COMMAND insert_vec_insert_elements)

add_executable(insert_append_rotate append_rotate.cpp)
target_link_libraries(insert_append_rotate PRIVATE doctest)
add_test(NAME "insert::append-rotate" COMMAND insert_append_rotate)

add_executable(insert_map_try_emplace map_try_emplace.cpp)
target_link_libraries(insert_map_try_emplace PRIVATE doctest)
add_test(NAME "insert::map-try-emplace" COMMAND insert_map_try_emplace)

add_executable(insert_map_extract map_extract.cpp)
target_link_libraries(insert_map_extract PRIVATE doctest)
add_test(NAME "insert::map-extract" COMMAND insert_map_extract)
