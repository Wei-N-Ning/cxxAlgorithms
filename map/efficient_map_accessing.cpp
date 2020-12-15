//
// Created by weining on 15/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <unordered_map>

// C++17 in detail P/2
// some new language syntax in C++17
// great to see it's learning from Golang

TEST_CASE( "Golang style if and assignment" )
{
    std::unordered_map< std::string, int > dict{ { "e1m1", 1 } };

    // automatic type deduction
    std::unordered_map aCopy{ dict };

    // C++17 in detail P/28; iter and wasAdded are "bindings" to a hidden temp pair (or tuple)
    // created by the compiler; the temp value has a unique identifier.
    if ( auto [ iter, wasAdded ] = dict.insert_or_assign( "e2m2", 2 ); !wasAdded )
    {
        // use the variable `wasAdded` to control whether to process the existing key-value or
        // to process the newly added key-value

        // here, the code should not be executed
        CHECK( false );
    }

    // another new syntax is the structured binding (tuple/pair decomposition)
    // there is an example in cxxFP/data_structure/range/factory_delimited.cpp
}

struct Item
{
    int x;
    int y;
};

TEST_CASE( "advance structured binding on struct" )
{
    // C++ 17 in detail P/31
    // x, y must be publicly accessible

    Item i{};
    auto &[ x, y ] = i;
    x = 123;
    CHECK_EQ( i.x, 123 );

    // I can even use x as a mutable ref - it can useful to model internal mutability
    auto f = []( int &x ) { x += 1; };
    f( x );
    CHECK_EQ( i.x, 124 );
}