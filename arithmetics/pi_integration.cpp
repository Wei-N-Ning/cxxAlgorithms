//
// Created by weining on 4/6/20.
//

// inspired by pro TBB P/115
// calculate the area of a circle using the numerical integration

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <iomanip>
#include <boost/iterator/counting_iterator.hpp>

// it is a rough approximation,
template < typename T = double, std::size_t num_intervals = 100 >
inline T pi()
{
    T dx = 1.0 / num_intervals;
    T sum = 0.0;
    for ( int i = 0; i < num_intervals; ++i )
    {
        T x = ( i + 0.5 ) * dx;
        T h = std::sqrt( 1 - x * x );
        sum += h * dx;
    }
    return 4 * sum;
}

template < typename T = double, std::size_t num_intervals = 100 >
inline T pi_take2()
{
    constexpr T dx = 1.0 / num_intervals;
    float sum = std::transform_reduce(
        boost::counting_iterator< int >( 0 ),
        boost::counting_iterator< int >( num_intervals ),
        0.0,
        []( auto x, auto y ) { return x + y; },
        [ = ]( int i ) {
            T x = ( i + 0.5 ) * dx;
            T h = std::sqrt( 1 - x * x );
            return h * dx;
        } );
    return 4 * sum;
}

TEST_CASE( "" )
{
    using namespace std;

    cout << std::setprecision( 15 ) << M_PI << endl << pi< double, 1000000 >() << endl;
    cout << std::setprecision( 15 ) << M_PI << endl << pi_take2< double, 1000000 >() << endl;

}
