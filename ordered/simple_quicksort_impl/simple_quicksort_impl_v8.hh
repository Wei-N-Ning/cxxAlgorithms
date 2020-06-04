//
// Created by weining on 4/6/20.
//

#ifndef CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V8_HH
#define CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V8_HH

template<typename It>
void qsort(It first, It last) {
    if (std::distance(first, last) > 1) {
        auto &pivot = *first;
        It p = last;
        for (auto i = last - 1; i > first; --i) {
            if (*i > pivot) std::swap(*i, *(--p));
        }
        std::swap(*(--p), *first);
        qsort(first, p);
        qsort(p + 1, last);
    }
}

#endif //CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V8_HH
