#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <algorithm>
#include <vector>
#include <utility>

// adv c++ faq
// read: https://en.cppreference.com/w/cpp/algorithm/partition_copy
// Copies the elements from the range [first, last) to two different ranges depending on the value
// returned by the predicate p. The elements that satisfy the predicate p are copied to the range
// beginning at d_first_true. The rest of the elements are copied to the range beginning at d_first_false.

TEST_CASE ("") {
    std::vector<int> v(300, 10);
    std::fill_n(std::back_inserter(v), 200, 9);
    std::vector<int> hd, tl;
    auto hd_tl = std::partition_copy(
        v.cbegin(), v.cend(),
        std::back_inserter(hd), std::back_inserter(tl),
        [](const auto &elem) {
            return elem >= 10;
        }
    );
    CHECK(hd.size() == 300);
    CHECK(std::all_of(hd.cbegin(), hd.cend(), [](const auto &elem) { return elem == 10; }));

    CHECK(tl.size() == 200);
    CHECK(std::all_of(tl.cbegin(), tl.cend(), [](const auto &elem) { return elem == 9; }));
}
