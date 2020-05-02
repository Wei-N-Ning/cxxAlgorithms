#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iterator>
#include <vector>
#include <cassert>

using V = std::vector<int>;

TEST_CASE ("test_equality()") {
    V v(10, 0);
    CHECK(v.cbegin() + 4 == v.end() - 6);
    CHECK(v.end() == v.cbegin() + v.size());
    CHECK(v.begin() - 1 != v.end());
}

TEST_CASE ("test_arithmetic_comparison()") {
    V v(10, 0);
    CHECK(v.begin() < v.cend());
    CHECK(v.begin() + 39 > v.cend());
    CHECK(10 == v.end() - v.cbegin());

    int a[8];
    CHECK(std::begin(a) < std::end(a));
    CHECK(std::begin(a) + 39 > std::end(a));
    CHECK(8 == std::end(a) - std::begin(a));
}
