//
// Created by weining on 9/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// c++ stl cookbook P/392
// see also: modern c++ cookbook P/2019 for a different histogram generation
// algorithm that uses a horizontal axis and a unicode for the bar character

template<typename RD>
void histogram(std::size_t partitions, std::size_t samples) {
    using namespace std;
    using rand_t = typename RD::result_type;
    partitions = max<size_t>(partitions, 10);

    // any random number gen needs to be instantiated as an object before use;
    // the resulting object can be called like a function without params
    RD rd;
    rand_t div{
        static_cast<rand_t>((double(RD::max()) + 1) / partitions)
    };
    vector<size_t> v(partitions);
    for (size_t i = 0; i < samples; ++i) {
        ++v[rd() / div];
    }

    rand_t max_elem{*max_element(cbegin(v), cend(v))};
    rand_t max_div{max(max_elem / 100, rand_t{1})};

    for (size_t i = 0; i < partitions; ++i) {
        cout << setw(2) << i << ": "
             << string(v[i] / max_div, '*')
             << endl;
    }
}

TEST_CASE ("") {
    using namespace std;
    cout << endl;
    cout << "//// default_random_engine" << endl;
    histogram<default_random_engine>(10, 100);
    cout << endl;
    cout << "//// minstd_rand0" << endl;
    histogram<minstd_rand0>(10, 100);
    cout << endl;
    cout << "//// minstd_rand" << endl;
    histogram<minstd_rand>(10, 100);
    cout << endl;
    cout << "//// mt19937" << endl;
    histogram<mt19937>(10, 100);
    cout << endl;
    cout << "//// mt19937_64" << endl;
    histogram<mt19937_64>(10, 100);
    cout << endl;
    cout << "//// ranlux24_base" << endl;
    histogram<ranlux24_base>(10, 100);
    cout << endl;
    cout << "//// ranlux48" << endl;
    histogram<ranlux48>(10, 100);
    cout << endl;
}
