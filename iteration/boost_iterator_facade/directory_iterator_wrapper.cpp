//
// Created by weining on 23/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/iterator/iterator_facade.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <numeric>
#include <sstream>

// this example is motivated by c++ 17 the complete guide P/270
// to prove that the parallel transform_reduce indeed must work with forward
// iterator.

namespace fs = std::filesystem;

template < bool Const = true >
class DirIterWrapper
    : public boost::iterator_facade< DirIterWrapper< Const >,
                                     std::conditional_t< Const, const std::string, std::string >,
                                     std::forward_iterator_tag >
{
    friend class boost::iterator_core_access;

    friend class DirIterWrapper< !Const >;

    fs::directory_iterator it;
    mutable std::string last{};
    fs::directory_iterator end{};

    [[nodiscard]] auto &dereference() const
    {
        last = it->path().string();
        return last;
    }

    void increment()
    {
        while ( it != end )
        {
            ++it;
            if ( it == end || it->is_regular_file() )
            {
                break;
            }
        }
    }

    // Support comparison between iterator and const_iterator types
    template < bool Const_ >
    bool equal( const DirIterWrapper< Const_ > &rhs ) const
    {
        return it == rhs.it;
    }

public:
    explicit DirIterWrapper( fs::directory_iterator dit ) : it( dit )
    {
    }

    // Support implicit conversion of iterator to const_iterator (but not vice versa)
    explicit operator DirIterWrapper< true >() const
    {
        return DirIterWrapper< true >{ it };
    }
};

TEST_CASE( "directory_iterator wrapper and motivation" )
{
    std::ostringstream oss;

    DirIterWrapper begin{ fs::directory_iterator( "/tmp" ) };
    DirIterWrapper end{ fs::directory_iterator{} };
    std::copy( begin, end, std::ostream_iterator< std::string >{ oss, "\n" } );

    // directory iterator works in std::copy, which takes InputIt
    std::copy( fs::directory_iterator( "/tmp" ),
               fs::directory_iterator{},
               std::ostream_iterator< fs::path >{ oss, "\n" } );

    // the non-parallel version of transform_reduce also takes InputIt therefore there is no need
    // to use the wrapper at all;
    // see cxxParallel/par_stl for further test with the parallel version
    std::transform_reduce(
        fs::directory_iterator( "/tmp" ),
        fs::directory_iterator{},
        0,
        // binary op
        []( const int &a, const int &b ) { return 0; },
        // unary transformer op
        []( const fs::path &path ) { return 0; } );
}

TEST_CASE( " use directory_iterator wrapper in transform_reduce" )
{
    DirIterWrapper begin{ fs::directory_iterator( "/tmp" ) };
    DirIterWrapper end{ fs::directory_iterator{} };
}