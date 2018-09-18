
add_tinytest_executable(vector_rotate
    vector_rotate.cpp)
set_target_properties(vector_rotate
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::rotate::vector"
    COMMAND vector_rotate)