add_executable(tree_simple_bst simple_bst.cpp)
target_link_libraries(tree_simple_bst PRIVATE doctest)
target_include_directories(tree_simple_bst PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "tree::simple-binary-search-tree" COMMAND tree_simple_bst)