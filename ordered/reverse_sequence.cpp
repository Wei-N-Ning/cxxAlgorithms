//
// Created by weining on 24/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iterator>
#include <vector>

void do_reverse(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    if (start == end) return;
    auto dis = std::distance(start, end);
    if (dis == 1) return;
    auto mid = start;
    std::advance(mid, dis / 2);
    do_reverse(start, mid);
    do_reverse(mid, end);
    std::rotate(start, mid, end);
}

TEST_CASE ("reverse: use forward iterator only") {
    // advance C++ fqa P/4
    using namespace std;

    {
        vector<int> v{1, 2, 3, 4};
        do_reverse(v.begin(), v.end());
        CHECK_EQ(vector<int>{4, 3, 2, 1}, v);
    }
    {
        vector<int> v{1, 2, 3, 4, 5};
        do_reverse(v.begin(), v.end());
        CHECK_EQ(vector<int>{5, 4, 3, 2, 1}, v);
    }
}