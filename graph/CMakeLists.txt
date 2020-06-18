
# test the graph class functionality
add_executable(graph_traversal_dagraph traversal/dagraph_tests.cpp traversal/dagraph.hh)
target_link_libraries(graph_traversal_dagraph PRIVATE doctest)
add_test(NAME "graph::traversal::dagraph" COMMAND graph_traversal_dagraph)

add_executable(graph_traversal_bfs traversal/bfs_tests.cpp)
target_link_libraries(graph_traversal_bfs PRIVATE doctest)
add_test(NAME "graph::traversal::bfs-tests" COMMAND graph_traversal_bfs)

add_executable(graph_boost_adjlist boost_graph_adjlist.cpp)
target_link_libraries(graph_boost_adjlist PRIVATE doctest)
target_include_directories(graph_boost_adjlist PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "graph::boost-adjlist" COMMAND graph_boost_adjlist)
