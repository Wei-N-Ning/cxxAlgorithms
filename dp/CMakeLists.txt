add_executable(dp_editing_distance editing_distance.cpp)
target_link_libraries(dp_editing_distance PRIVATE doctest)
add_test(NAME "DP::editing_distance" COMMAND dp_editing_distance)