//
// Created by weining on 7/6/20.
//

// source: effective STL

// std::equal_range()
// std::lower_bound()
// std::upper_bound()

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <algorithm>
#include <list>

TEST_CASE ("find all matching elements") {
    std::list<int> l{1, 2, 3, 3, 4, 5, 6};
    {
        auto[first, last] = std::equal_range(std::cbegin(l), std::cend(l), 3);
        CHECK_EQ(*first, 3);
        CHECK_EQ(*last, 4);  // point to the element AFTER the last matching element
    }
    {
        // Finds the first position in which @a val could be inserted
        //   *         without changing the ordering
        auto it = std::lower_bound(std::cbegin(l), std::cend(l), 3);
        CHECK_EQ(*it, 3);
    }
    {
        // An iterator pointing to the first element greater than @p __val,
        //   *           or end() if no elements are greater than @p __val.
        auto it = std::upper_bound(std::cbegin(l), std::cend(l), 3);
        CHECK_EQ(*it, 4);
    }
}
