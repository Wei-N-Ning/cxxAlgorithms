
# test the graph class functionality
add_executable(graph_traversal_dagraph traversal/dagraph_tests.cpp traversal/dagraph.hh)
target_link_libraries(graph_traversal_dagraph PRIVATE doctest)
add_test(NAME "graph::traversal::dagraph" COMMAND graph_traversal_dagraph)

add_executable(graph_traversal_bfs traversal/bfs_tests.cpp)
target_link_libraries(graph_traversal_bfs PRIVATE doctest)
add_test(NAME "graph::traversal::bfs-tests" COMMAND graph_traversal_bfs)
