//
// Created by weining on 24/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// read: <https://en.cppreference.com/w/cpp/algorithm/stable_partition>
// NOTE: C++17 adds par execution policy

// adv c++ faq P/17

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

TEST_CASE ("") {
    using namespace std;
    vector<int> v{3, 14, 1, 5, 92, 6, 53, 58, 97};
    auto pos = stable_partition(v.begin(), v.end(), [](const auto &n) { return n > 10; });
    copy(v.begin(), pos, ostream_iterator<int>{cout, " "});
    cout << endl;
    copy(pos, v.end(), ostream_iterator<int>{cout, " "});
    cout << endl;
}
