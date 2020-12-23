//
// Created by weining on 24/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <map>
#include <string>
#include <unordered_map>
#include <sstream>

// c++ 17 the complete guide P/293
// you can also use the node handles to move elements from a container to
// another. the containers can even differ in the following way:
// - one supports duplicates while another does not (map -> multimap)
// - comparison functions and hash functions might differ

template < typename A, typename B >
std::ostream& operator<<( std::ostream& os, const std::pair< A, B >& pr )
{
    os << "(" << pr.first << ", " << pr.second << ")";
    return os;
}

TEST_CASE( "extract insert between containers of different types" )
{
    std::map< std::string, int > m{ { "e1m1", 10 } };
    std::multimap< std::string, int > mm{ { "e1m1", 1 } };

    auto nh = m.extract( "e1m1" );
    mm.insert( std::move( nh ) );

    auto [ begin, end ] = mm.equal_range( "e1m1" );

    std::ostringstream oss;
    for ( auto it = begin; it != end; ++it )
    {
        oss << *it << '\n';
    }
    CHECK_EQ( oss.str(), "(e1m1, 1)\n(e1m1, 10)\n" );

    // move nodes from multimap to map
    // P/294
    {
        auto [ pos, successful, nodeHandle ] = m.insert( mm.extract( "e1m1" ) );
        // pos: iterator pointing to the existing element if inserting was not possible
        // successful
        // nodeHandle: if inserting was not possible

        // this time, it successfully moves (e1m1, 1) from mm to m
        CHECK( successful );
    }
    {
        auto [ pos, successful, nodeHandle ] = m.insert( mm.extract( "e1m1" ) );

        // this time, it fails because m already has a key `e1m1`, which maps to 1
        // therefore the iterator pos points to (e1m1, 1);
        // nodeHandle is (e1m1, 10) that is extracted from mm
        CHECK_FALSE( successful );
        std::cout << *pos << '\n';
    }
}
