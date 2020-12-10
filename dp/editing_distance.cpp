//
// Created by weining on 11/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <utility>
#include <unordered_set>
#include <random>

// revisit the classic dp problem: minimum editing distance (Levenshtein distance)
// with the focus on clarity and FP
// see FP in c++ P/132

// FP in c++ P/133
// it is sometimes useful to be able to put a function into a wrapper and
// automatically get the memoized version of the function out.
// the general structure for caching, when you can't predict what arguments
// the function will be invoked with, is a map.

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

namespace hash_tuple
{
template < typename TT >
struct hash
{
    size_t operator()( TT const& tt ) const
    {
        return std::hash< TT >()( tt );
    }
};
}  // namespace hash_tuple

TEST_CASE( "is STL tuple hashable? (if all the members are)" )
{
    // source:
    // https://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set
    // if I were to create a cache to store the results from arbitrary pure functions
    // I need to ensure the arguments, passed in as a single tuple, are hashable
    // I need a workaround like so -

    // however the real working example uses std::map to avoid the hashing issue at all

    using memoized_key_t = std::tuple< size_t, size_t, std::string >;
    std::unordered_map< memoized_key_t, size_t, hash_tuple::hash< memoized_key_t > > cache;
}

// make_memoized does NOT work with lambda objects
template < typename Result, typename... Args >
auto make_memoized( Result ( *f )( Args... ) )
{
    using _key_t = std::tuple< Args... >;
    std::map< _key_t, Result > cache;

    // each lambda returned will have ITS OWN CACHE - very important!!!
    return [ f, cache ]( Args... args ) mutable -> Result {
        const auto args_tuple = std::make_tuple( args... );
        const auto cached = cache.find( args_tuple );
        if ( cached == cache.end() )
        {
            auto result = f( args... );
            cache[ args_tuple ] = result;
            return result;
        }
        else
        {
            return cached->second;
        }
    };
}

size_t withEffect( size_t x )
{
    std::random_device rd;
    std::mt19937 g( rd() );
    return g() * x;
}

TEST_CASE( "make_memoized (freezing the effect)" )
{
    auto f = make_memoized( withEffect );
    CHECK_EQ( f( 10 ), f( 10 ) );
}
