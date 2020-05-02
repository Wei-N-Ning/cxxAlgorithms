
add_executable(insert_vec_insert_elements vec_insert_elements.cpp)
target_link_libraries(insert_vec_insert_elements PRIVATE doctest)
add_test(NAME "insert::vector-insert-elements" COMMAND insert_vec_insert_elements)

add_executable(insert_append_rotate append_rotate.cpp)
target_link_libraries(insert_append_rotate PRIVATE doctest)
add_test(NAME "insert::append-rotate" COMMAND insert_append_rotate)
