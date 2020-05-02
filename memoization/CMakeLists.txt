add_executable(memoization_lookup lookup.cc)
target_link_libraries(memoization_lookup PRIVATE doctest)
add_test(NAME "memoization::lookup" COMMAND memoization_lookup)