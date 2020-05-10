
add_executable(arithmetic_isnan isnan.cc)
add_test(NAME "arithmetic::isnan" COMMAND arithmetic_isnan)

add_executable(arithmetic_gcd gcd.cpp)
target_link_libraries(arithmetic_gcd PRIVATE doctest)
add_test(NAME "arithmetic::gcd" COMMAND arithmetic_gcd)

add_executable(arithmetic_precision precision.cc)
add_test(NAME "arithmetic::precision" COMMAND arithmetic_precision)

add_executable(arithmetic_fourier_trans fourier_trans.cpp)
target_link_libraries(arithmetic_fourier_trans PRIVATE doctest)
target_include_directories(arithmetic_fourier_trans PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "arithmetic::fourier-trans" COMMAND arithmetic_fourier_trans)

add_executable(arithmetic_limits limits.cpp)
target_link_libraries(arithmetic_limits PRIVATE doctest)
add_test(NAME "arithmetic::limits" COMMAND arithmetic_limits)