
add_subdirectory(rotation)
add_subdirectory(insertion)
add_subdirectory(sliding)
#add_subdirectory(reversing)

add_executable(std_accumulate std_accumulate.cpp)
set_target_properties(std_accumulate
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::algorithm::accumulate"
    COMMAND std_accumulate)

add_executable(std_count std_count.cpp)
set_target_properties(std_count
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::algorithm::count"
    COMMAND std_count)

add_executable(std_equal std_equal.cpp)
set_target_properties(std_equal
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::algorithm::equal"
    COMMAND std_equal)

add_executable(std_generate std_generate.cpp)
set_target_properties(std_generate
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::algorithm::generate"
    COMMAND std_generate)

add_executable(std_transform std_transform.cpp)
set_target_properties(std_transform
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::algorithm::transform"
    COMMAND std_transform)

add_executable(std_find_if std_find_if.cpp)
set_target_properties(std_find_if
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::algorithm::find_if"
    COMMAND std_find_if)

add_executable(std_inner_product std_inner_product.cpp)
set_target_properties(std_inner_product
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "std::algorithm::inner_product"
    COMMAND std_inner_product)


add_executable(std_advance std_advance/vector.cpp)
set_target_properties(std_advance
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "container::std-advance"
    COMMAND std_advance)

add_executable(std_remove std_remove/vector.cpp)
set_target_properties(std_remove
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "container::std-remove"
    COMMAND std_remove)

add_executable(std_unpack_tuple_pair unpack/tuple_pair_unpack.cpp)
target_link_libraries(std_unpack_tuple_pair PRIVATE doctest)
add_test(NAME "container::unpack::tuple-pair" COMMAND std_unpack_tuple_pair)
