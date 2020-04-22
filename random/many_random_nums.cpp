// source:
// https://www.fluentcpp.com/2019/05/24/how-to-fill-a-cpp-collection-with-random-values/
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <random>
#include <iostream>
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
    std::vector<int> nums{5000};
    std::generate(nums.begin(), nums.end(), [&dist, &random_engine]() { return dist(random_engine); });
}