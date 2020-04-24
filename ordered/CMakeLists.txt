
add_executable(reverse_sequence reverse_sequence.cpp)
target_link_libraries(reverse_sequence PRIVATE doctest)
add_test(NAME "ordered::reverse-sequence" COMMAND reverse_sequence)

add_executable(swap_section swap_section.cpp)
target_link_libraries(swap_section PRIVATE doctest)
add_test(NAME "ordered::swap-section" COMMAND swap_section)

add_executable(slide_section slide_section.cpp)
target_link_libraries(slide_section PRIVATE doctest)
add_test(NAME "ordered::slide-section" COMMAND slide_section)