//
// Created by weining on 10/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <iostream>

// FP in c++ P/127
// this chapter talks about lazy evaluation and how to use it to optimize
// existing algorithms;
// one of the use case is partial sort:
// given a collection of sortable values, find out a n smallest/biggest values
// STL provides std::nth_element() function, see:
// https://en.cppreference.com/w/cpp/algorithm/nth_element
// nth_element is a partial sorting algorithm that rearranges elements in [first, last) such that:
//
//    The element pointed at by nth is changed to whatever element would occur in that position
//    if [first, last) were sorted.
//    All of the elements before this new nth element are less than or equal to the elements after
//    the new nth element.
TEST_CASE( "use std::nth_element to partially sort a vector (largest/smallest n elements)" )
{
    std::vector< int > xs( 1000, 0 );
    std::generate( xs.begin(), xs.end(), [ n = 1 ]() mutable { return ++n; } );
    auto p = std::find( xs.begin(), xs.end(), 6 );
    std::nth_element( xs.begin(), p, xs.end() );
    std::for_each( xs.begin(), xs.begin() + 10, []( const auto &x ) { std::cout << x << ' '; } );
    std::cout << '\n';
}