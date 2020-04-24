// source:
// https://www.fluentcpp.com/2019/05/24/how-to-fill-a-cpp-collection-with-random-values/
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <random>
#include <iostream>
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
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
}
