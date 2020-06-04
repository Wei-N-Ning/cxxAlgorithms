//
// Created by weining on 4/6/20.
//

#ifndef CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V7_HH
#define CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V7_HH

template<typename It>
void qsort(It first, It last) {
    if (std::distance(first, last) > 1) {
        auto &pivot = *first;
        It i = last;
        for (auto j = last - 1; j > first; --j) {
            if (*j > pivot) std::swap(*j, *(--i));
        }
        std::swap(*(--i), *first);
        qsort(first, i);
        qsort(i + 1, last);
    }
}

#endif //CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V7_HH
