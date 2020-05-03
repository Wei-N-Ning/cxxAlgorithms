//
// Created by weining on 3/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/timer/timer.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

// c++ stl cookbook P/47
// NOTE: the naive() method is actually faster because the sequence to be erased
// are nicely packed together; this results in O(1)
// the remove-erase method has to do m-swap to relocate the elements to the end
// which results in O(N)

TEST_CASE ("remove_naive()") {
    using namespace std;
    cout << "remove_naive()" << endl;

    // 11 ... 11 22 ... 22 00 ... 00;
    size_t sz_two =   500001;
    size_t sz_one =   500002;
    size_t sz_zero = 1000004;
    vector<int> v(sz_two + sz_one + sz_zero, 0);
    fill_n(v.begin(), sz_one, 1);
    fill_n(v.begin() + sz_one, sz_two, 2);

    {
        boost::timer::auto_cpu_timer t;
        v.erase(v.begin() + sz_one, v.begin() + sz_one + sz_two);
        CHECK_EQ(sz_one + sz_zero, v.size());
    }
}

TEST_CASE ("erase_remove()") {
    using namespace std;
    cout << "erase_remove()" << endl;

    // 11 ... 11 22 ... 22 00 ... 00;
    size_t sz_two =   500001;
    size_t sz_one =   500002;
    size_t sz_zero = 1000004;
    vector<int> v(sz_two + sz_one + sz_zero, 0);
    fill_n(v.begin(), sz_one, 1);
    fill_n(v.begin() + sz_one, sz_two, 2);

    {
        boost::timer::auto_cpu_timer t;
        const auto new_end = remove(begin(v), end(v), 2);
        v.erase(new_end, end(v));

        // slightly faster:
        // v.resize(v.size() - distance(new_end, end(v)));
        CHECK_EQ(sz_one + sz_zero, v.size());
    }
}
