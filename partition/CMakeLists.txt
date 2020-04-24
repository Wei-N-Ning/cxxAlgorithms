add_executable(stable_partition stable_partition.cpp)
target_link_libraries(stable_partition PRIVATE doctest)
add_test(NAME "partition::stable-partition" COMMAND stable_partition)