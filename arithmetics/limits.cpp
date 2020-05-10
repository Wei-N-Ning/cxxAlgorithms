//
// Created by weining on 11/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <limits>
#include <bitset>

// modern c++ programming cookbook L1808

TEST_CASE ("") {
    auto imin{std::numeric_limits<int>::min()};
    auto smax{std::numeric_limits<std::size_t>::max()};

    using Bits = std::bitset<std::numeric_limits<std::size_t>::digits>;
    auto bits = Bits{0b1001} & Bits{0b0111};
    CHECK_EQ(bits, 1);
}
