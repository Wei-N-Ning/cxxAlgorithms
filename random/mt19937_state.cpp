//
// Created by weining on 11/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <array>
#include <algorithm>
#include <random>
#include <iostream>
#include <iterator>

// modern c++ cookbook P/2039
// worth comparing the perform between this version and the default/lazy version

TEST_CASE ("properly initialize a pseudo-random number generator to produce"
           "the best sequence") {
    using namespace std;

    random_device rd;
    array<int, mt19937::state_size> seed_data{};
    // rd is not copyable (the copy ctor is deleted), therefore I can only pass
    // &rd (bad) or std::ref(rd)
    generate(begin(seed_data), end(seed_data), ref(rd));
    seed_seq seq(begin(seed_data), end(seed_data));
    mt19937 eng{seq};
    uniform_int_distribution<> dist{1, 20};

    generate_n(ostream_iterator<int>{cout, " "}, 10,
        [&eng, &dist]() { return dist(eng); });
    cout << endl;
}
