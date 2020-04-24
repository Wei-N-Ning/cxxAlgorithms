
add_executable(arithmetic_isnan isnan.cc)
add_test(NAME "arithmetics::isnan" COMMAND arithmetic_isnan)

add_executable(arithmetic_gcd gcd.cpp)
target_link_libraries(arithmetic_gcd PRIVATE doctest)
add_test(NAME "arithmetic::gcd" COMMAND arithmetic_gcd)