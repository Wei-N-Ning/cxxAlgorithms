//
// Created by weining on 11/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// revisit the classic dp problem: minimum editing distance (Levenshtein distance)
// with the focus on clarity and FP
// see FP in c++ P/132

TEST_CASE( "unoptimized editing distance" )
{
    // the unoptimized version will run for a long time when the length of the
    // inputs goes larger than 10-12

    // as in the unoptimized fib implementation, there is no "pruning" of
    // the recursion tree, leading to excessive re-computation of the same
    // intermediate values

    // FP in c++ P/133
    // lev(m, n) is a pure function; the result always depends only on its
    // argument, and it has no side effects.
    // you can not have more than m * n different results
    // the only way the implementation can have exponential complexity is if
    // it calculates the same thing multiple times.
    // NOTE:
    // what a great explanation!
    // this old problem looks more noble in the light of FP
    std::string src{ "idfa" };
    std::string dst{ "idkfa" };

    std::function< size_t( size_t, size_t ) > lev = [ & ]( size_t m, size_t n ) -> size_t {
        return m == 0   ? n
               : n == 0 ? m
                        : std::min( { lev( m - 1, n ) + 1,
                                      lev( m, n - 1 ) + 1,
                                      lev( m - 1, n - 1 ) + ( src[ m - 1 ] != dst[ n - 1 ] ) } );
    };

    auto o = lev( src.length(), dst.length() );
    CHECK_EQ( o, 1 );
}