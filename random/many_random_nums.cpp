// source:
// https://www.fluentcpp.com/2019/05/24/how-to-fill-a-cpp-collection-with-random-values/
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <chrono>
#include <random>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

TEST_CASE ("generate single random int") {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> distribution_1_100(1, 100);
    auto randomNumber = distribution_1_100(random_engine);
    std::cout << randomNumber << std::endl;
}

TEST_CASE ("generate many random ints") {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> dist(1, 100);
    std::vector<int> nums(50);
    // std::generate
    // https://en.cppreference.com/w/cpp/algorithm/generate
    auto gen = [&dist, &random_engine]() { return dist(random_engine); };
    std::generate(nums.begin(), nums.end(), gen);
    std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
    std::generate_n(nums.begin(), nums.size(), gen);
    std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
}

// source: https://en.cppreference.com/w/cpp/algorithm/random_shuffle
TEST_CASE ("poor man's random number generator") {
    size_t sz = 32;
    std::vector<int> v(sz);
    std::generate(v.begin(), v.end(), [&sz]() { return sz--; });
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    std::cout << "// Poor man #1" << std::endl;
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
}

template<typename T>
void poorman_vector(std::size_t sz, std::vector<T> &o_vec) {
    o_vec.resize(sz);
    std::ifstream ifs{"/dev/urandom", std::ifstream::binary};
    ifs.read((char *) o_vec.data(), sizeof(T) * sz);
    ifs.close();
}

// this only supports vector
// inspired by : https://gist.github.com/mortenpi/9745042
TEST_CASE ("poor man's random number generator #2: /dev/urandom") {
    std::vector<int> v;
    poorman_vector(12, v);
    std::cout << "// Poor man #2" << std::endl;
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
}

template<typename T, typename RD = std::default_random_engine>
void lazyman_vector(std::size_t sz, std::vector<T> &o_vec, T mi, T mx) {
    using namespace std::chrono;
    // see: https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
    // for high_resolution_clock, see
    // https://en.cppreference.com/w/cpp/chrono/high_resolution_clock
    // NOTE: as of gcc 9.1, high_resolution_clock is an alias of system_clock
    std::size_t seed = high_resolution_clock::now().time_since_epoch().count();
    // RD rd(seed);

    // modern c++ cookbook: L1990
    // to avoid the security risk (of having a deterministic seed), use the
    // random device
    RD rd(std::random_device{}());
    std::uniform_int_distribution<T> dist(mi, mx);
    o_vec.resize(sz);
    std::generate(std::begin(o_vec), std::end(o_vec),
        [&dist, &rd]() { return dist(rd); });
}

TEST_CASE ("lazy man's random number generator: time-seeded") {
    std::vector<int> v;
    lazyman_vector(12, v, -1223, 1213);
    std::cout << "// Lazy man" << std::endl;
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
}