
add_executable(stl_accumulate std_accumulate.cpp)
add_test(NAME "stl::accumulate" COMMAND stl_accumulate)

add_executable(stl_count std_count.cpp)
add_test(NAME "stl::count" COMMAND stl_count)

add_executable(stl_equal std_equal.cpp)
add_test(NAME "stl:equal" COMMAND stl_equal)

add_executable(stl_generate std_generate.cpp)
add_test(NAME "stl::generate" COMMAND stl_generate)

add_executable(stl_transform std_transform.cpp)
add_test(NAME "stl::transform" COMMAND stl_transform)

add_executable(stl_find_if std_find_if.cpp)
add_test(NAME "stl::find_if" COMMAND stl_find_if)

add_executable(stl_inner_product std_inner_product.cpp)
add_test(NAME "stl::inner_product" COMMAND stl_inner_product)

add_executable(stl_compare_iter compare_iter.cpp)
target_link_libraries(stl_compare_iter PRIVATE doctest)
add_test(NAME "stl::compare-iterators" COMMAND stl_compare_iter)

add_executable(stl_auto_if_switch_var auto_if_switch_variable.cpp)
target_link_libraries(stl_auto_if_switch_var PRIVATE doctest)
add_test(NAME "stl::auto-if-switch-variables" COMMAND stl_auto_if_switch_var)

