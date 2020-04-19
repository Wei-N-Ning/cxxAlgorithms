add_executable(std_rand std_rand.cpp bsd_drand48.cpp bsd_drand48.hh)
target_link_libraries(std_rand PUBLIC m)
add_test(NAME "std::random::test-drand48" COMMAND std_rand)

add_executable(uuid_to_string uuid_to_string.cpp)
target_link_libraries(uuid_to_string PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(uuid_to_string PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "random::boost-uuid-to-string" COMMAND uuid_to_string)

add_executable(string_to_uuid string_to_uuid.cpp)
target_link_libraries(string_to_uuid PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(string_to_uuid PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "random::boost-string-to-uuid" COMMAND string_to_uuid)
