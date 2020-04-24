
add_executable(reverse_sequence reverse_sequence.cpp)
target_link_libraries(reverse_sequence PRIVATE doctest)
add_test(NAME "ordered::reverse-sequence" COMMAND reverse_sequence)
