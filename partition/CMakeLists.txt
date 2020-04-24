add_executable(parition_stable_partition stable_partition.cpp)
target_link_libraries(parition_stable_partition PRIVATE doctest)
add_test(NAME "partition::stable-partition" COMMAND parition_stable_partition)

add_executable(partition_copy partition_copy.cpp)
target_link_libraries(partition_copy PRIVATE doctest)
add_test(NAME "partition::partition-copy" COMMAND partition_copy)