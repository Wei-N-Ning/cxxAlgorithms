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
#include <functional>

// c++ stl cookbook P/392
// see also: modern c++ cookbook P/2019 for a different histogram generation
// algorithm that uses a horizontal axis and a unicode for the bar character
// UPDATE:
// follow modern c++ cookbook P/2039, and implement an initialization function
// that populates all the seed bits for mt19937 - compare the default-constructed
// mt19937 (and its 64bit variant) with the fully-initialized version.
// the latter shows more even distribution (fair randomness)
// see mt19937_state.cpp for a dedicated example

template<typename RD>
void initialize_state(RD &rd) {
    ;
}

template<>
void initialize_state(std::mt19937 &rd_) {
    using namespace std;

    random_device rd;
    array<int, mt19937::state_size> seed_data{};
    generate(begin(seed_data), end(seed_data), ref(rd));
    seed_seq seq(begin(seed_data), end(seed_data));
    rd_ = mt19937{seq};
}

template<>
void initialize_state(std::mt19937_64 &rd_) {
    using namespace std;

    random_device rd;
    array<int, mt19937_64::state_size> seed_data{};
    generate(begin(seed_data), end(seed_data), ref(rd));
    seed_seq seq(begin(seed_data), end(seed_data));
    rd_ = mt19937_64{seq};
}

template<typename RD>
void histogram(std::size_t partitions, std::size_t samples, bool require_initialization = false) {
    using namespace std;
    using rand_t = typename RD::result_type;
    partitions = max<size_t>(partitions, 10);

    // any random number gen needs to be instantiated as an object before use;
    // the resulting object can be called like a function without params
    RD rd;
    if (require_initialization) {
        initialize_state(rd);
    }

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

    size_t n_partitions = 10;
    size_t n_samples = 400;

    cout << endl;
    cout << "//// default_random_engine" << endl;
    histogram<default_random_engine>(n_partitions, n_samples);
    cout << endl;
    cout << "//// minstd_rand0" << endl;
    histogram<minstd_rand0>(n_partitions, n_samples);
    cout << endl;
    cout << "//// minstd_rand" << endl;
    histogram<minstd_rand>(n_partitions, n_samples);
    cout << endl;
    cout << "//// mt19937" << endl;
    histogram<mt19937>(n_partitions, n_samples);
    cout << endl;
    cout << "//// mt19937 initialized" << endl;
    histogram<mt19937>(n_partitions, n_samples, true);
    cout << endl;
    cout << "//// mt19937_64" << endl;
    histogram<mt19937_64>(n_partitions, n_samples);
    cout << endl;
    cout << "//// mt19937_64 initialized" << endl;
    histogram<mt19937_64>(n_partitions, n_samples, true);
    cout << endl;
    cout << "//// ranlux24_base" << endl;
    histogram<ranlux24_base>(n_partitions, n_samples);
    cout << endl;
    cout << "//// ranlux48" << endl;
    histogram<ranlux48>(n_partitions, n_samples);
    cout << endl;
}
