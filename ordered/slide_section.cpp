//
// Created by weining on 24/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <vector>

TEST_CASE ("") {
    using namespace std;
    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    //            .     .        .
    size_t n_step = 3;
    rotate(v.begin(), v.begin() + 2, v.begin() + 2 + n_step);
    CHECK_EQ(vector<int>{3, 4, 5, 1, 2, 6, 7}, v);
}
