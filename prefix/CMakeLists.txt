
add_executable(prefix_subarr_equals_k subarr_equals_k.cpp)
target_link_libraries(prefix_subarr_equals_k PRIVATE doctest)
add_test(NAME "prefix::subarr-equals-to-k" COMMAND prefix_subarr_equals_k)
