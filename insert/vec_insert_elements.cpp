//
// Created by weining on 24/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <iterator>
#include <vector>

template<typename F, typename G>
void do_insert(F &haystack, G first, G last, size_t n) {
    auto sz = haystack.size();
    haystack.insert(haystack.end(), first, last);
    std::rotate(haystack.begin() + n, haystack.begin() + sz, haystack.end());
}

TEST_CASE ("insert: append & rotate") {
    // advanced c++ qa P/2
    // must know the position and the number of elements
    using namespace std;
    vector<int> haystack{3, 14, 1, 5, 9};
    //                         ^
    vector<int> elements{2, 3, 4};
    do_insert(haystack, elements.cbegin(), elements.cend(), 2);
    CHECK_EQ(vector<int>{3, 14, 2, 3, 4, 1, 5, 9}, haystack);
}
