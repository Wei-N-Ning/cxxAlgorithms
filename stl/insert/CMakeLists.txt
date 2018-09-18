
add_tinytest_executable(append_rotate append_rotate.cpp)
set_target_properties(append_rotate
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::efficient-insert::append-rotate"
    COMMAND append_rotate)