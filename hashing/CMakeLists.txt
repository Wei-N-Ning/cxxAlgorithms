add_executable(hashing_function hash_function.cpp)
add_test(NAME "hashing::hash-function" COMMAND hashing_function)