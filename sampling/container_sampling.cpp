//
// Created by weining on 21/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <algorithm>
#include <vector>
#include <set>
#include <numeric>
#include <random>
#include <iostream>

// c++ 17 in detail P/242
// it saves the use of a random shuffle on a temporary vector

TEST_CASE( "take samples from vector and place them into an ordered set" )
{
    std::vector xs( 10000, 0 );
    std::iota( xs.begin(), xs.end(), 0 );
    constexpr size_t numSamples = 10;
    std::set< int > ys;
    std::sample( xs.cbegin(),
                 xs.cend(),
                 std::inserter( ys, ys.begin() ),
                 numSamples,
                 // still require a random generator
                 std::mt19937{ std::random_device{}() } );
    std::for_each( ys.cbegin(),
                   ys.cend(),
                   //
                   []( const auto &y ) { std::cout << y << ' '; } );
    std::cout << '\n';
}