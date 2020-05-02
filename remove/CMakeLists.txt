add_executable(remove_vector_elements vector_remove_elements.cpp)
target_link_libraries(remove_vector_elements PRIVATE doctest)
add_test(NAME "remove::remove-elements-from-vector" COMMAND remove_vector_elements)
