//
// Created by weining on 24/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <numeric>

// adv c++ faq P/26
// reference: https://en.cppreference.com/w/cpp/numeric/gcd
TEST_CASE ("") {

    CHECK_EQ(7, std::gcd(28, 21));
    CHECK_EQ(7, std::gcd(21, 28));
}
