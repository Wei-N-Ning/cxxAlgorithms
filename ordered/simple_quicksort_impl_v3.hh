//
// Created by weining on 2/6/20.
//

#ifndef CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V3_HH
#define CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V3_HH

template<typename It>
auto partition(It lo, It hi) {
    It i = lo - 1;  // set cursor
    for (auto j = lo; j < hi; ++j) {  // range excludes the pivot
        if (*j < *hi) std::swap(*(++i), *j);  // each time cursor moves, it swaps a weak for a strong
    }
    std::swap(*(++i), *hi);  // if cursor moves again, it is guaranteed to point to a strong
    return i;   // swap the strong for the pivot, and returns its position
}

template<typename It>
void qsort(It lo, It hi) {
    if (lo < hi) {
        auto p = partition(lo, hi);
        qsort(lo, p - 1);
        qsort(p + 1, hi);
    }
}

#endif //CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V3_HH
