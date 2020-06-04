//
// Created by weining on 2/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include "simple_quicksort_impl/simple_quicksort_impl_v8.hh"
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

template<typename T, typename RD = std::default_random_engine>
void lazyman_vector(std::size_t sz, std::vector<T> &o_vec, T mi, T mx) {
    using namespace std::chrono;
    std::size_t seed = high_resolution_clock::now().time_since_epoch().count();
    RD rd(std::random_device{}());
    std::uniform_int_distribution<T> dist(mi, mx);
    o_vec.resize(sz);
    std::generate(std::begin(o_vec), std::end(o_vec),
                  [&dist, &rd]() { return dist(rd); });
}

TEST_CASE ("compare with std::sort") {
    std::vector<int> v1{3, 1, 4};
    std::vector<int> v2{v1};
    qsort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    CHECK_EQ(v1, v2);

    std::vector<int> v3{3, 14, 1, 5, 3, 1, 3, 1, 3, 1, 4, 6, 9, 10, 11};
    std::vector<int> v4{v3};
    qsort(v3.begin(), v3.end());
    std::sort(v4.begin(), v4.end());
    CHECK_EQ(v3, v4);

    std::vector<int> v5;
    lazyman_vector(100, v5, -12312, 43242);
    std::vector<int> v6{v5};
    qsort(v5.begin(), v5.end());
    std::sort(v6.begin(), v6.end());
    CHECK_EQ(v5, v6);
}
