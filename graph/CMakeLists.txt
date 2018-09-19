
add_tinytest_executable(graph_traversal_dagraph_tests
    traversal/dagraph_tests.cpp)
set_target_properties(graph_traversal_dagraph_tests
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME
    "graph::traversal::dagraph-tests"
    COMMAND
    graph_traversal_dagraph_tests
)

add_tinytest_executable(graph_traversal_bfs_tests
    traversal/bfs_tests.cpp)
set_target_properties(graph_traversal_bfs_tests
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME
    "graph::traversal::bfs-tests"
    COMMAND
    graph_traversal_bfs_tests
)