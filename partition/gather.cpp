//
// Created by weining on 5/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <algorithm>
#include <iterator>
#include <vector>
#include <numeric>
#include <iostream>
#include <utility>
#include <functional>  // for std::not_fn in lower version of gcc

// c++ stl cookbook P/252
// NOTE: this algorithm is also explained in depth in Advance C++ Q&A, the first section
//

template<typename It, typename F>
std::pair<It, It> gather(It begin, It end, It gather_pos, F predicate) {
    return {
        std::stable_partition(begin, gather_pos, std::not_fn(predicate)),
        std::stable_partition(gather_pos, end, predicate)
    };
}

TEST_CASE ("") {
    std::vector<int> v(20, 1);
    std::iota(std::next(v.begin(), 3), v.end(), -4);
    std::iota(std::prev(v.end(), 2), v.end(), -9);
    auto gather_pos = std::find(v.begin(), v.end(), 9);
    auto dump = [&v]() {
        std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>{std::cout, " "});
        std::cout << std::endl;
    };
    dump();
    gather(v.begin(), v.end(), gather_pos, [](const auto &elem) { return elem < 0; });
    dump();
}
