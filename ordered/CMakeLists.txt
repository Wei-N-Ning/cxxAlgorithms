
add_executable(ordered_reverse_sequence reverse_sequence.cpp)
target_link_libraries(ordered_reverse_sequence PRIVATE doctest)
add_test(NAME "ordered::reverse-sequence" COMMAND ordered_reverse_sequence)

add_executable(ordered_swap_section swap_section.cpp)
target_link_libraries(ordered_swap_section PRIVATE doctest)
add_test(NAME "ordered::swap-section" COMMAND ordered_swap_section)

add_executable(ordered_slide_section slide_section.cpp)
target_link_libraries(ordered_slide_section PRIVATE doctest)
add_test(NAME "ordered::slide-section" COMMAND ordered_slide_section)