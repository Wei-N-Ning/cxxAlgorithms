//
// Created by weining on 20/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cstddef>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using Bytes = std::vector< std::byte >;
using Byte = std::byte;

TEST_CASE( "create byte sequence from std::string" )
{
    std::string ss{ "iddqd" };
    Bytes xs( ss.size() );
    std::transform( ss.cbegin(),
                    ss.cend(),
                    xs.begin(),
                    //
                    []( const char &ch ) { return Byte( ch ); } );
}

TEST_CASE( "create byte sequence from string stream" )
{
    std::stringstream ss{ "iddqd" };
    Bytes xs( 5 );
    ss.read( ( char * )xs.data(), 5 );
}
