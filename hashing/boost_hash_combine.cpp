//
// Created by weining on 10/6/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/functional/hash.hpp>
#include <vector>

TEST_CASE ("demo combine") {
    std::size_t seed = 0;
    boost::hash_combine(seed, "asd");
    boost::hash_combine(seed, 0.21);
    boost::hash_combine(seed, std::vector<int>{1, 1, 2,});

}
