add_executable(random_std_rand std_rand.cpp bsd_drand48.cpp bsd_drand48.hh)
target_link_libraries(random_std_rand PUBLIC m)
add_test(NAME "std::random::test-drand48" COMMAND random_std_rand)

add_executable(random_uuid_to_string uuid_to_string.cpp)
target_link_libraries(random_uuid_to_string PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(random_uuid_to_string PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "random::boost-uuid-to-string" COMMAND random_uuid_to_string)

add_executable(random_string_to_uuid string_to_uuid.cpp)
target_link_libraries(random_string_to_uuid PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(random_string_to_uuid PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "random::boost-string-to-uuid" COMMAND random_string_to_uuid)

add_executable(random_uniform_dist_rand uniform_dist_rand.cpp)
target_link_libraries(random_uniform_dist_rand PRIVATE doctest)
target_include_directories(random_uniform_dist_rand PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "random::std-uniform-distribution-random" COMMAND random_uniform_dist_rand)

add_executable(random_many_random_nums many_random_nums.cpp)
target_link_libraries(random_many_random_nums PRIVATE doctest)
add_test(NAME "random::many-random-numbers" COMMAND random_many_random_nums)

add_executable(random_rand_histogram rand_histogram.cpp)
target_link_libraries(random_rand_histogram PRIVATE doctest)
add_test(NAME "random::rand-histogram" COMMAND random_rand_histogram)

add_executable(random_stl_distribution stl_distribution.cpp)
target_link_libraries(random_stl_distribution PRIVATE doctest)
add_test(NAME "random::stl-distribution" COMMAND random_stl_distribution)

add_executable(random_mt19937_state mt19937_state.cpp)
target_link_libraries(random_mt19937_state PRIVATE doctest)
add_test(NAME "random::mt19937-state" COMMAND random_mt19937_state)
