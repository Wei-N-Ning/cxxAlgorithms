
add_tinytest_executable(vector_sliding
    vector_sliding.cpp)
set_target_properties(vector_sliding
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::sliding"
    COMMAND vector_sliding)
