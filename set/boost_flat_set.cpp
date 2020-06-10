//
// Created by weining on 11/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/container/flat_set.hpp>
#include <iostream>
#include <algorithm>
#include <iterator>

// boost c++ app dev P/275
// use flat set to improve cache alignment by sacrificing index speed (O(1) -> O(n))
// see also: boost/container/flat_map
// other advantages over std::set
// - distance() is O(1)
// - provide random access iterators

// boost flat set properties:
// - faster look up than standard associative ctn
// - much faster iter speed than standard associative ctn
// - memory and cache
// - non stable iters; random access
// - weaker exception safety
// - slower insertion

TEST_CASE ("") {
    // storage backend is vector
    boost::container::flat_set<int> fs{1, 2, 2, 3, 4, 1, 4, 1};
    std::copy(std::cbegin(fs), std::cend(fs), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;

}