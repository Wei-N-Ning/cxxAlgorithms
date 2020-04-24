//
// Created by weining on 24/4/20.
//

// advance C++ fqa P/5
// ... [ i , i + n - 1 ] [ i + n , j - 1 ] [ j , j + n - 1 ] ...
// start                                       end
// rotate(i, j, j + n)
// ... [ i + n , j - 1 ] [ j , j + n - 1 ] [ i , i + n - 1 ] ...
// rotate(i + n, j, j + n - 1)
// ... [ j , j + n - 1 ] [ i + n , j - 1 ] [ i , i + n - 1 ]

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <vector>

// adv c++ faq P/13
// std::rotate is superior to swap_range because it can handle two subsequences of different length
template<typename F, typename G>
size_t swap_range(F first1, F last1, G first2) {
    size_t n_swapped = 0;
    for (; first1 != last1; ++first1, ++first2, ++n_swapped) {
        std::swap(*first1, *first2);
    }
    return n_swapped;
}

TEST_CASE ("swap_range()") {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    auto n_swapped = swap_range(v.begin(), v.begin() + 2, v.begin() + 2);
    CHECK_EQ(2, n_swapped);
    CHECK_EQ(std::vector<int>{3, 4, 1, 2, 5, 6}, v);
}
