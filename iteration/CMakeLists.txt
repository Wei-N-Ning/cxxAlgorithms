add_executable(iteration_custom_iterator_forloop custom_iterator_forloop.cpp)
target_link_libraries(iteration_custom_iterator_forloop PRIVATE doctest)
add_test(NAME "iteration::custom-iterator-forloop" COMMAND iteration_custom_iterator_forloop)

add_executable(iteration_custom_iterator_range custom_iterator_range.cpp)
target_link_libraries(iteration_custom_iterator_range PRIVATE doctest)
add_test(NAME "iteration::custom-iterator-range" COMMAND iteration_custom_iterator_range)

add_executable(iteration_fib_iter fib_iter.cpp)
target_link_libraries(iteration_fib_iter PRIVATE doctest)
add_test(NAME "iteration::fibonacci-number-iterator" COMMAND iteration_fib_iter)

add_executable(iteration_zip_iter zip_iter.cpp)
target_link_libraries(iteration_zip_iter PRIVATE doctest)
target_include_directories(iteration_zip_iter PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "iteration::zip-iterators" COMMAND iteration_zip_iter)

add_executable(iteration_neighbour_elements iter_neighbour_elements.cpp)
target_link_libraries(iteration_neighbour_elements PRIVATE doctest)
target_include_directories(iteration_neighbour_elements PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "iteration::neighbour-elements" COMMAND iteration_neighbour_elements)

add_executable(iteration_boost_iterator_facade boost_iterator_facade.cpp)
target_link_libraries(iteration_boost_iterator_facade PRIVATE doctest)
target_include_directories(iteration_boost_iterator_facade PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "iteration::boost-iterator-facade" COMMAND iteration_boost_iterator_facade)

add_executable(iteration_run_length_encoding run_length_encoding.cpp)
target_link_libraries(iteration_run_length_encoding PRIVATE doctest)
add_test(NAME "iteration::run-length-encoding" COMMAND iteration_run_length_encoding)

add_executable(iteration_zip_tuples zip_tuples.cpp)
target_link_libraries(iteration_zip_tuples PRIVATE doctest)
add_test(NAME "iteration::zip-tuples" COMMAND iteration_zip_tuples)

add_executable(iteration_boost_iterator_facade_putc boost_iterator_facade_putc.cpp)
target_link_libraries(iteration_boost_iterator_facade_putc PRIVATE doctest)
target_include_directories(iteration_boost_iterator_facade_putc PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "iteration::boost-iterator-facade-putc" COMMAND iteration_boost_iterator_facade_putc)

