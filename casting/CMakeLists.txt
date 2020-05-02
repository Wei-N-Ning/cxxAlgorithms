
add_executable(casting_const_cast const_cast.cpp)
add_test(NAME "casting::const-cast" COMMAND casting_const_cast)

add_executable(casting_pointer_to_uint pointer_to_uint.cpp)
add_test(NAME "casting::pointer-to-uint" COMMAND casting_pointer_to_uint)