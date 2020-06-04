//
// Created by weining on 2/6/20.
//

#ifndef CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V1_HH
#define CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V1_HH

#include <algorithm>

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
template<typename It>
auto partition(It lo, It hi) {
    auto &pivot = *hi;
    It i = lo - 1;
    for (It j = lo; j <= hi - 1; ++j) {
        if (*j < pivot) {
            ++i;
            std::swap(*i, *j);
        }
    }
    // this also works, using std::for_each
//    std::for_each(lo, hi, [&i, &pivot](auto &elem) {
//        if (elem < pivot) {
//            ++i;
//            std::swap(*i, elem);
//        }
//    });
    std::swap(*(i + 1), *hi);
    return i + 1;
}

template<typename It>
void qsort(It lo, It hi) {
    if (lo < hi) {
        auto p = partition(lo, hi);
        qsort(lo, p - 1);
        qsort(p + 1, hi);
    }
}

#endif //CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V1_HH
