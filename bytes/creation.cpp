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

// c++ 17 the complete guide P/171
// std::byte brings more type safety as this type can not easily be
// abused as an integral value or character type;
// the only computing operation supported are bit-wise operators

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

TEST_CASE( "create byte variable with byte literal" )
{
    // c++ 17 the complete guide P/171
    // uses two new c++ 14 features:
    // - prefix 0b for binary literals
    // - digit separator '
    std::byte b2{ 0b1111'0000 };
}