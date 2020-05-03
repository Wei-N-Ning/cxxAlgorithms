add_executable(hashing_function hash_function.cpp)
add_test(NAME "hashing::hash-function" COMMAND hashing_function)

add_executable(hashing_hash_map hash_map.cpp)
target_link_libraries(hashing_hash_map PRIVATE doctest)
add_test(NAME "hashing::hash-map" COMMAND hashing_hash_map)