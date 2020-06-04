//
// Created by weining on 4/6/20.
//

#ifndef CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V6_HH
#define CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V6_HH

template<typename It>
auto partition(It first, It last) {
    auto &pivot = *first;
    It i = last;  // set the cursor
    for (auto j = last - 1; j > first; --j) {  // range excludes the pivot
        if (*j > pivot) std::swap(*j, *(--i));   // as i moves backward, it collects the strong
    }
    std::swap(*(--i), *first);  // i moves backward again, points to a weak; swap it for the pivot
    return i;  // return the position of the pivot
}

template<typename It>
void qsort(It first, It last) {
    if (std::distance(first, last) > 1) {  // account for the half-open range;
        auto p = partition(first, last);
        qsort(first, p);  // range: [first, p-1] (or [first, p) )
        qsort(p + 1, last);  // range: [p + 1, last-1] (or [p + 1, last) )
    }
}

#endif //CXXALGORITHMS_SIMPLE_QUICKSORT_IMPL_V6_HH
