//
// Created by wein on 18/09/18.
//

//
// 0 1 2 3 4 5 6 7 8 9
//        |------*
// to slide 7 to the position before 4

// source
// C++ FAQ P14
// this is can be solved nicely by std::rotate
// the term for this pattern is "slide" as explained in the chapter in
// this book "generic slide function"

// IMPORTANT: <from> and <to> must be tested to make sure rotating in
// the correct direction

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <cassert>

template<typename Elem>
static void slide(std::vector<Elem>& v, 
                  size_t fromIdx,
                  size_t toIdx,
                  size_t numElements) {
    if (fromIdx < toIdx) {
        if (toIdx < v.size() &&
            fromIdx + numElements < v.size())
        {
            std::rotate(
                v.begin() + fromIdx,
                v.begin() + fromIdx + numElements,
                v.begin() + toIdx + 1
            );
        }
    } else if (fromIdx > toIdx) {
        if (fromIdx < v.size() &&
            fromIdx + numElements < v.size()) {
            std::rotate(
                v.begin() + toIdx,
                v.begin() + fromIdx,
                v.begin() + fromIdx + numElements
            );
        }
    }
}

template<typename Elem>
static void verify(const std::vector<Elem>& actual, const std::vector<Elem>& expected) {
    bool success = std::equal(
        actual.cbegin(),
        actual.cend(),
        expected.begin());
    assert(success);
}

template<typename Elem>
static void pprint(const std::vector<Elem>& v) {
    std::ostream_iterator<Elem> it(std::cout, " ");
    std::copy(v.cbegin(), v.cend() - 1, it);
    std::cout << v.back() << std::endl;
}

TEST_CASE ("test_slide_one_element()") {
    std::vector<int> haystack(10, 0), expected(10, 0);
    
    // low to high
    haystack = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //                      *--------|
    expected = {0, 1, 2, 3, 5, 6, 7, 4, 8, 9};
    
    slide(haystack, 4, 7, 1);
    verify(haystack, expected);

    // high to low
    haystack = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //                |--------*
    expected = {0, 1, 5, 2, 3, 4, 6, 7, 8, 9};
    slide(haystack, 5, 2, 1);
    verify(haystack, expected);

    // output bound, expect no change to haystack
    haystack = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    slide(haystack, 4, 7, 100);
    verify(haystack, expected);
    slide(haystack, 7, 4, 100);
    verify(haystack, expected);
    slide(haystack, 3, 100, 1);
    verify(haystack, expected);
    slide(haystack, 123, 3, 1);
    verify(haystack, expected);

    // overlapping
    haystack = {0, 1, 2, 3, 4};
    slide(haystack, 3, 3, 1);
    verify(haystack, std::vector<int>{0, 1, 2, 3, 4});  // no changes

    // adjacent elements 
    slide(haystack, 2, 3, 1);
    verify(haystack, std::vector<int>{0, 1, 3, 2, 4});
    slide(haystack, 3, 2, 1);
    verify(haystack, std::vector<int>{0, 1, 2, 3, 4});  
}

// Note the use of "numElements" instead of hardcoding it to 1
TEST_CASE ("test_slide_multiple_elements()") {
    std::vector<int> haystack(10, 0), expected(10, 0);
    
    // cross over, numElements >= abs(from - to)
    // expect "capping" at the rear
    haystack = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //                      .............
    expected = {0, 1, 2, 3, 9, 4, 5, 6, 7, 8};
    slide(haystack, 4, 7, 3);
    pprint(haystack);
}
