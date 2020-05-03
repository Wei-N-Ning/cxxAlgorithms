//
// Created by weining on 3/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <deque>
#include <iterator>
#include <iostream>

// c++ stl cookbook P/110
// showing how to use iterator adapter to insert at front, middle and back in
// a deque
// NOTE how front insert reverses the order of the needle elements

TEST_CASE ("") {
    std::deque<std::string> dq;
    std::deque<std::string> needle{"E1", "M1", "IDDQD"};
    std::copy_n(std::begin(needle), 3,  std::back_inserter(dq));
    std::copy_n(std::begin(needle), 2, std::front_inserter(dq));
    std::copy_n(std::begin(needle), 2, std::inserter(dq, dq.begin() + 2));

    std::copy(dq.cbegin(), dq.cend(), std::ostream_iterator<std::string>{std::cout, " "});
    // M1 E1 E1 M1 E1 M1 IDDQD
    // front  mid   back
}
