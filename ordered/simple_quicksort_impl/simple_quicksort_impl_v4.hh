//
// Created by weining on 3/6/20.
//

#ifndef CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V4_HH
#define CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V4_HH

template<typename It>
auto partition(It lo, It hi) {
    auto &pivot = *hi;
    It i = lo - 1;
    for (auto j = lo; j < hi; ++j) {
        if (*j < pivot) std::swap(*j, *(++i));
    }
    std::swap(*(++i), *hi);
    return i;
}

template<typename It>
void qsort(It lo, It hi) {
    if (lo < hi) {
        auto p = partition(lo, hi);
        qsort(lo, p - 1);
        qsort(p + 1, hi);
    }
}

#endif //CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V4_HH
