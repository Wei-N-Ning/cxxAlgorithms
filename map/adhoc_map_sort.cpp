//
// Created by weining on 22/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <map>

// c++ 17 the complete guide P/78

// this is to demonstrate a limitation rather than a feature of c++ 17:

// there is no partial class template resolution.

// because of this, it is not possible to simplify the instantiation of the
// std::map template in a one-liner:
// std::map<Key, Value> = m{[](const Key &l, const Key &r) {...}};

// I have to define the lambda sort function first and then pass its decltype
// to the map instantiation

// the same two-step-dance applies to std::set and std::unordered_... (hash
// function)

struct Item
{
    int u;
    int v;
};

using Rank = int;

TEST_CASE( "provide sort function for custom type on the fly" )
{
    auto lessThan = []( const Item &l, const Item &r ) {
        return std::tie( l.u, l.v ) < std::tie( r.u, r.v );
    };
    std::map< Item, Rank, decltype( lessThan ) > m{ lessThan };

    // c++ 17 emplace and insert
    // see: https://en.cppreference.com/w/cpp/container/map/insert
    m.emplace( Item{ 1, 2 }, 10 );
    m.insert( { { -12, 3 }, 20 } );

    {
        const auto &[ k, v ] = *m.cbegin();
        CHECK_EQ( v, 20 );
    }
    {
        const auto &[ k, v ] = *( std::prev( m.cend() ) );
        CHECK_EQ( v, 10 );
    }
}