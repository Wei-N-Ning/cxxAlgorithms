
add_executable(isnan isnan.cc)
add_test(
    NAME "arithmetics::isnan"
    COMMAND
    isnan
)

add_executable(gcd gcd.cpp)
target_link_libraries(gcd PRIVATE doctest)
add_test(NAME "arithmetic::gcd" COMMAND gcd)