//
// Created by weining on 28/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <random>
#include <string>
#include <iostream>

// this is motivated by haskell's quickcheck library that can generates random string ([Char]) with
// easy

TEST_CASE( "default random engine generating string" )
{
    std::uniform_int_distribution< char > aToD( 'a', 'd' );
    std::random_device random_device;
    std::mt19937 eng( random_device() );
    aToD( eng );
    std::string s{ "    " };
    for ( auto i = 0; i < 100; ++i )
    {
        std::generate( s.begin(), s.end(), [ & ]() { return aToD( eng ); } );
        std::cout << s << '\n';
    }
}
