//
// Created by weining on 22/5/20.
//

// optimized c++ L6329
// see also: https://en.cppreference.com/w/cpp/container/map/insert_or_assign

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <map>
#include <unordered_map>

TEST_CASE( "bintree map" )
{
    std::map< int, int > m{ { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 } };
    m.insert_or_assign( 50, 50 );

    // search for key
    if ( auto it = m.find( 50 ); it != m.end() )
    {
        ;  // it->second
    }
}

TEST_CASE( "hash map" )
{
    std::unordered_map< int, int > m{ { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 } };
    m.insert_or_assign( 50, 50 );

    // search for key
    if ( auto it = m.find( 50 ); it != m.end() )
    {
        ;  // it->second
    }
}
