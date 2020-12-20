//
// Created by weining on 20/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cstddef>
#include <vector>
#include <sstream>

using Bytes = std::vector< std::byte >;

TEST_CASE( "create byte sequence" )
{
    std::stringstream ss{ "iddqd" };
    Bytes xs( 100 );
}