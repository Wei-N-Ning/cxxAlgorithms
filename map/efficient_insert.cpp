//
// Created by weining on 22/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <map>
#include <unordered_map>

// optimized c++ L6329
// see also: https://en.cppreference.com/w/cpp/container/map/insert_or_assign

// c++ 17 in detail P/236
// with c++ 17 you get two new methods for maps and unordered_maps
// try_emplace(): if the obj already exists then it does nothing, otherwise it
//                behaves like emplace()
// emplace() might move from the input parameter when the key is in the map,
//     that is why it is best to use find() before such emplacement
// insert_or_assign() gives more information than operator[], as it returns
// if the element was newly inserted or updated and also works with types
// that have no default ctor

// see also efficient_insert.cpp

TEST_CASE( "bintree map" )
{
    std::map< int, int > m{ { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 } };
    auto [ _, wasAdded ] = m.insert_or_assign( 50, 50 );

    // search for key
    if ( auto it = m.find( 50 ); it != m.end() )
    {
        ;  // it->second
    }
}

TEST_CASE( "hash map" )
{
    std::unordered_map< int, int > m{ { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 } };
    auto [ _, wasAdded ] = m.insert_or_assign( 50, 50 );

    // search for key
    if ( auto it = m.find( 50 ); it != m.end() )
    {
        ;  // it->second
    }
}

TEST_CASE( "try_emplace" )
{
    std::unordered_map< std::string, std::string > m;
    m[ "e1m1" ] = "32";
    m[ "e1m2" ] = "64";
    std::string s{ "213" };
    // will not move s, key `e1m1` exists
    m.try_emplace( "e1m1", std::move(s) );

    s = "213";
    // will make s in an invalid state, key `e2m2` does not exist
    m.try_emplace( "e2m2", std::move( s ) );

}
