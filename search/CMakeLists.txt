add_executable(search_trie trie.cpp)
target_link_libraries(search_trie PRIVATE doctest)
add_test(NAME "search::trie" COMMAND search_trie)

add_executable(search_first_in_range_sorted first_in_range/sorted.cpp)
target_link_libraries(search_first_in_range_sorted PRIVATE doctest)
add_test(NAME "search::first-in-range::sorted" COMMAND search_first_in_range_sorted)
