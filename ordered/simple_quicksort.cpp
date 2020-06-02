//
// Created by weining on 2/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

// https://en.wikipedia.org/wiki/Quicksort
// https://www.geeksforgeeks.org/cpp-program-for-quicksort/

// algorithm quicksort(A, lo, hi) is
//    if lo < hi then
//        p := partition(A, lo, hi)
//        quicksort(A, lo, p - 1)
//        quicksort(A, p + 1, hi)
//
//algorithm partition(A, lo, hi) is
//    pivot := A[hi]
//    i := lo
//    for j := lo to hi do
//        if A[j] < pivot then
//            swap A[i] with A[j]
//            i := i + 1
//    swap A[i] with A[hi]
//    return i

// performance analysis
// c's qsort vs std::sort
// https://www.geeksforgeeks.org/c-qsort-vs-c-sort/
// std::sort
// https://www.geeksforgeeks.org/sort-c-stl/
template<typename C, typename It>
auto partition(C &A, It lo, It hi) {
    auto &pivot = *hi;
    It i = lo - 1;
    for (It j = lo; j <= hi - 1; j++) {
        if (*j <= pivot) {
            i++;
            std::swap(*i, *j);
        }
    }
    std::swap(*(i + 1), *hi);
    return i + 1;
}

template<typename C, typename It>
void qsort(C &A, It lo, It hi) {
    if (lo < hi) {
        auto p = partition(A, lo, hi);
        qsort(A, lo, p - 1);
        qsort(A, p + 1, hi);
    }
}

TEST_CASE ("compare with std::sort") {
    std::vector<int> v1{3, 1, 4};
    std::vector<int> v2{v1};
    qsort(v1, v1.begin(), v1.end() - 1);
    std::sort(v2.begin(), v2.end());
    CHECK_EQ(v1, v2);

    std::vector<int> v3{3, 14, 1, 5, 3, 1, 3, 1, 3, 1, 4, 6, 9, 10, 11};
    std::vector<int> v4{v3};
    qsort(v3, v3.begin(), v3.end() - 1);
    std::sort(v4.begin(), v4.end());
    CHECK_EQ(v3, v4);
}
