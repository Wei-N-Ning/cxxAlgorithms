add_executable(test_hashing test_hashing.cpp)
set_target_properties(test_hashing
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME cxxUsage::algorithms::hashing
    COMMAND test_hashing)