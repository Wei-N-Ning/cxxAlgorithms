//
// Created by weining on 19/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/range/algorithm.hpp>
#include <boost/range/irange.hpp>

#include <iostream>
#include <random>
#include <vector>
#include <iterator>

// source:
// https://en.cppreference.com/w/cpp/numeric/random/random_device
std::vector<int> generate_ints(int min, int max, int size) {
    using namespace std;
    random_device rd;  // used for seed
    // to generate uniformly distributed pseudo-random numbers, between min and max
    uniform_int_distribution<int> dist(min, max);
    vector<int> v;
    v.reserve(size);
    // do not use auto ref - won't type check; irange is not a real container
    boost::transform(boost::irange(0, size), back_inserter(v), [&rd, &dist](auto _) { return dist(rd); });
    return v;
};

TEST_CASE ("generate N pseudo random numbers within range") {
    using namespace std;
    auto v = generate_ints(-12, 12, 3);
    boost::copy(v, ostream_iterator<int>{std::cout, "\n"});
    CHECK_EQ(3, v.size());
}