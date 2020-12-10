//
// Created by weining on 10/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <iostream>
#include <random>

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
    std::vector< int > xs( 20, 0 );
    std::generate( xs.begin(), xs.end(), [ n = 1 ]() mutable { return n++; } );

    std::random_device rd;
    std::mt19937 g( rd() );
    std::shuffle( xs.begin(), xs.end(), g );

    //  p will point to the 6th largest element
    std::nth_element( xs.begin(), xs.end() - 6, xs.end() );

    // ensure these largest/smallest elements are fully sorted, which is `k log(k)`
    // the total time cost is `n + k log(k)`
    // see FP c++ P/128
    std::sort( xs.end() - 6, xs.end() );
    std::for_each( xs.begin(), xs.end(), []( const auto &x ) { std::cout << x << ' '; } );
    std::cout << " mid: " << *( xs.end() - 6 ) << '\n';
}
