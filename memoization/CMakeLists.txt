add_tinytest_executable(memoization
    lookup.cc)
set_target_properties(memoization
    PROPERTIES
    CXX_STANDARD 17)
add_test(
    NAME
    "memoization::lookup"
    COMMAND
    memoization
)