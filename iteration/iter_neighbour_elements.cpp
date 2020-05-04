//
// Created by weining on 4/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/iterator/zip_iterator.hpp>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

// inspired by c++ stl cookbook P/238
// the example the book uses std::inner_product to process the elements from
// two containers of the same length, in a pair-wise manner
// this strongly reminds me zip-iterator

// for reference, there are some popular implementation of zip-iterator:

// boost's zip-iterator accepts 2 ranges and yields an std::pair for each pair;
// see:
// https://www.boost.org/doc/libs/1_72_0/libs/iterator/doc/zip_iterator.html

// Intel's TBB offers a zip-iterator that accepts N ranges, and yields an std::tuple
// for each element group
// see:
// https://www.threadingbuildingblocks.org/docs/help/reference/iterators/zip_iterator.html

// both of them require the ranges are of the same length

// range-v3, offers range-view, can combine 2 ranges, similar to boost's

// finally, I find this post that explains std::inner_product and how to exploit
// to process each two adjacent elements in a range
// https://marcoarena.wordpress.com/2017/11/14/a-hidden-gem-inner_product/

// having used Haskell's zipWith and zip-n functions, I know how useful this
// can be, such as iterating over a range of elements, process every K adjacent
// elements each time etc.

// the example below uses std::inner_product for demonstration

TEST_CASE ("") {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    // std::cbegin(v), )
    // std::prev(std::cbegin(v), 1), std::cend(v))
    std::inner_product(
        std::cbegin(v), std::prev(std::cend(v), 1),
        std::next(std::cbegin(v), 1),
        // init
        0,
        // sum function
        [](auto acc, auto _) {
            return acc;
        },
        // pair-wise function
        [](const auto &l, const auto &r) {
            std::cout << l << " " << r << ",";
            return 0;
        }
    );
    std::cout << std::endl;

}
