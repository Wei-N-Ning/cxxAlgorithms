//
// Created by weining on 3/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <vector>
#include <iostream>

TEST_CASE ("") {
    std::vector<unsigned long long> v{1, 1};
    std::size_t idx{2};
    std::generate_n(std::back_inserter(v), 100, [&v, &idx]() {
        auto n = v[idx - 1] + v[idx - 2];
        idx++;
        return n;
    });
    std::cout << v[80] << std::endl;
}
