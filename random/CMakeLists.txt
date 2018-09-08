add_executable(std_rand
    std_rand.cpp
    bsd_drand48.cpp
    bsd_drand48.hh)
set_target_properties(std_rand
    PROPERTIES
    CXX_STANDARD 14)
target_link_libraries(std_rand
    PUBLIC
    m)
add_test(
    NAME
    "std::random::test-drand48"
    COMMAND
    std_rand
)