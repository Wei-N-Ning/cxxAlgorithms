
add_executable(vec_insert_elements vec_insert_elements.cpp)
target_link_libraries(vec_insert_elements PRIVATE doctest)
add_test(NAME "insert::vector-insert-elements" COMMAND vec_insert_elements)
