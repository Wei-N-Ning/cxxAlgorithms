add_executable(hashing_function hash_function.cpp)
add_test(NAME "hashing::hash-function" COMMAND hashing_function)

add_executable(hashing_hash_map hash_map.cpp)
target_link_libraries(hashing_hash_map PRIVATE doctest)
add_test(NAME "hashing::hash-map" COMMAND hashing_hash_map)

add_executable(hashing_boost_hash boost_hash.cpp)
target_link_libraries(hashing_boost_hash PRIVATE doctest)
target_include_directories(hashing_boost_hash PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "hashing::boost-hash" COMMAND hashing_boost_hash)
