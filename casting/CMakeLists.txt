
add_executable(constCastTest const_cast.cpp)
set_target_properties(constCastTest
    PROPERTIES
    CXX_STANDARD 17
    CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror"
    )