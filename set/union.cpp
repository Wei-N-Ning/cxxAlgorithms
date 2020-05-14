//
// Created by weining on 14/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

// modern c++ programming cookbook L4854

// see also:
// set_intersect
// set_difference
// std::includes
// std::merge
TEST_CASE ("") {
    using namespace std;

    vector<int> v1{1, 2, 3, 4, 6};
    vector<int> v2{2, 4, 6, 8};
    set_union(begin(v1), end(v1), begin(v2), end(v2), ostream_iterator<int>{cout, " "});
    cout << endl;
}