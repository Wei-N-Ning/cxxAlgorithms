
add_executable(isnan isnan.cc)
add_test(
    NAME "arithmetics::isnan"
    COMMAND
    isnan
)