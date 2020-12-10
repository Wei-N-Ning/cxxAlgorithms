
add_executable(ordered_reverse_sequence reverse_sequence.cpp)
target_link_libraries(ordered_reverse_sequence PRIVATE doctest)
add_test(NAME "ordered::reverse-sequence" COMMAND ordered_reverse_sequence)

add_executable(ordered_swap_section swap_section.cpp)
target_link_libraries(ordered_swap_section PRIVATE doctest)
add_test(NAME "ordered::swap-section" COMMAND ordered_swap_section)

add_executable(ordered_slide_section slide_section.cpp)
target_link_libraries(ordered_slide_section PRIVATE doctest)
add_test(NAME "ordered::slide-section" COMMAND ordered_slide_section)

add_executable(ordered_vector_sliding vector_sliding.cpp)
target_link_libraries(ordered_vector_sliding PRIVATE doctest)
add_test(NAME "ordered::vector-sliding" COMMAND ordered_vector_sliding)

add_executable(ordered_rotate_vector vector_rotate.cpp)
target_link_libraries(ordered_rotate_vector PRIVATE doctest)
add_test(NAME "ordered::vector" COMMAND ordered_rotate_vector)

add_executable(ordered_set_sort set_sort.cpp)
# this uses target-dependent query, part of the generator-syntax, of cmake
# see: https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#target-dependent-queries
add_test(NAME "ordered::script" COMMAND echo 1 2 3 | $<TARGET_FILE:ordered_rotate_vector>)

add_executable(ordered_advance_iterator advance_iterator.cpp)
target_link_libraries(ordered_advance_iterator PRIVATE doctest)
add_test(NAME "ordered::advance-iterator" COMMAND ordered_advance_iterator)

add_executable(ordered_priority_queue priority_queue.cpp)
target_link_libraries(ordered_priority_queue PRIVATE doctest)
add_test(NAME "ordered::priority-queue" COMMAND ordered_priority_queue)

add_executable(ordered_list_merge list_merge.cpp)
target_link_libraries(ordered_list_merge PRIVATE doctest)
add_test(NAME "ordered::list-merge" COMMAND ordered_list_merge)

add_executable(ordered_simple_quicksort simple_quicksort.cpp)
target_link_libraries(ordered_simple_quicksort PRIVATE doctest)
add_test(NAME "ordered::simple-quicksort" COMMAND ordered_simple_quicksort)

add_executable(ordered_simple_heapsort simple_heapsort.cpp)
target_link_libraries(ordered_simple_heapsort PRIVATE doctest)
add_test(NAME "ordered::simple-heapsort" COMMAND ordered_simple_heapsort)

add_executable(ordered_partial_sort partial_sort.cpp)
target_link_libraries(ordered_partial_sort PRIVATE doctest)
add_test(NAME "ordered::partial_sort" COMMAND ordered_partial_sort)
