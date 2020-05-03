add_executable(remove_vector_elements vector_remove_elements.cpp)
target_link_libraries(remove_vector_elements PRIVATE doctest)
add_test(NAME "remove::remove-elements-from-vector" COMMAND remove_vector_elements)

add_executable(remove_vector_erase_remove vector_erase_remove.cpp)
target_link_libraries(remove_vector_erase_remove PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(remove_vector_erase_remove PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "remove::erase-remove-idiom" COMMAND remove_vector_erase_remove)
