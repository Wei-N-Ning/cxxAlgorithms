add_executable(search_trie trie.cpp)
target_link_libraries(search_trie PRIVATE doctest)
add_test(NAME "search::trie" COMMAND search_trie)
