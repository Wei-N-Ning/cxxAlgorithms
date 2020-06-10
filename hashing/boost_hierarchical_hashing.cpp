//
// Created by weining on 10/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/functional/hash.hpp>
#include <vector>
#include <algorithm>

TEST_CASE ("hash elements") {
    std::vector<int> v(100, 100);
    auto h = boost::hash_range(std::cbegin(v), std::cend(v));

    // hash_range is equivalent to:
    std::size_t seed = 0;
    std::for_each(std::cbegin(v), std::cend(v), [&seed](const auto &elem) { boost::hash_combine(seed, elem); });

    CHECK_EQ(h, seed);

    // for a tree of nodes:
    // hierarchical hash is O(n)
    // but hash-comparison (fast diff-ing) AT ANY LEVEL becomes O(1)
}
