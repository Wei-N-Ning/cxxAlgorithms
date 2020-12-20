
add_executable(bytes_create_bytes creation.cpp)
target_link_libraries(bytes_create_bytes PRIVATE doctest)
add_test(NAME "bytes::create" COMMAND bytes_create_bytes)