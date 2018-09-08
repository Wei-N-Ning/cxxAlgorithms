add_executable(base16demo base16/demoBase16.cc)
set_target_properties(base16demo
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "base16demo" COMMAND base16demo)