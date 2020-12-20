//
// Created by weining on 20/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <set>

// c++ 17 in detail P/236
// "move" an entry from set-1 to set-2 while avoiding excessive copies

struct Item
{
    int value;
    explicit Item( int x ) : value( x )
    {
    }

    friend bool operator<( const Item &i1, const Item &i2 )
    {
        return i1.value < i2.value;
    }
};

TEST_CASE( "c++17 extract insert" )
{
    std::set< Item > s1;
    s1.emplace( 1 );

    std::set< Item > s2;
    s2.emplace( 2 );

    auto entry = s1.extract( Item{ 1 } );
    s2.insert( std::move( entry ) );

    CHECK_EQ( s2.size(), 2 );
    CHECK_EQ( s1.size(), 0 );
}