
add_executable(std_accumulate std_accumulate.cpp)
add_test(NAME "std::algorithm::accumulate" COMMAND std_accumulate)

add_executable(std_count std_count.cpp)
add_test(NAME "std::algorithm::count" COMMAND std_count)

add_executable(std_equal std_equal.cpp)
add_test(NAME "std::algorithm::equal" COMMAND std_equal)

add_executable(std_generate std_generate.cpp)
add_test(NAME "std::algorithm::generate" COMMAND std_generate)

add_executable(std_transform std_transform.cpp)
add_test(NAME "std::algorithm::transform" COMMAND std_transform)

add_executable(std_find_if std_find_if.cpp)
add_test(NAME "std::algorithm::find_if" COMMAND std_find_if)

add_executable(std_inner_product std_inner_product.cpp)
add_test(NAME "std::algorithm::inner_product" COMMAND std_inner_product)

add_executable(std_unpack_tuple_pair unpack/structural_binding.cpp)
target_link_libraries(std_unpack_tuple_pair PRIVATE doctest)
add_test(NAME "container::unpack::tuple-pair" COMMAND std_unpack_tuple_pair)
