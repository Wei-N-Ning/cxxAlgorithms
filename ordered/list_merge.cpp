//
// Created by weining on 22/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <list>

TEST_CASE ("") {
    std::list<int> l1{1, 2, 3}, l2{5, 6, 7};
    l1.merge(l2);
    CHECK_EQ(std::list<int>{1, 2, 3, 5, 6, 7}, l1);
}