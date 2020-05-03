add_executable(iteration_custom_iterator custom_iterator.cpp)
target_link_libraries(iteration_custom_iterator PRIVATE doctest)
add_test(NAME "iteration::custom-iterator" COMMAND iteration_custom_iterator)

add_executable(iteration_custom_iterator_stl custom_iterator_stl.cpp)
target_link_libraries(iteration_custom_iterator_stl PRIVATE doctest)
add_test(NAME "iteration::custom-iterator-stl" COMMAND iteration_custom_iterator_stl)



