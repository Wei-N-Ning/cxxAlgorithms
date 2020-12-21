//
// Created by weining on 21/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <numeric>

// c++ 17 in detail P/243
// see also:
// https://en.cppreference.com/w/cpp/header/cmath
// https://en.cppreference.com/w/cpp/numeric

TEST_CASE( "least common multiple" )
{
    CHECK_EQ( 150, std::lcm( 15, 50 ) );
}