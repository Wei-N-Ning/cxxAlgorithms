//
// Created by weining on 24/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <iterator>
#include <vector>

TEST_CASE ("insert: append & rotate") {
    // advanced c++ qa P/2
    // must know the position and the number of elements
    using namespace std;
    vector<int> haystack{3, 14, 1, 5, 9};
    vector<int> elements{2, 3, 4};
    auto do_insert = [from = elements.cbegin(), to = elements.cend(), &haystack]() {
        haystack.insert(haystack.end(), from, to);
        std::rotate(haystack.begin() + 3, haystack.begin() + 4, haystack.end());
    };
    do_insert();
    CHECK_EQ(vector<int>{3, 14, 1, 2, 3, 4, 5, 9}, haystack);
}
