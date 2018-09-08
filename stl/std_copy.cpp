
// source
// mentioned in more exception item 13, lazy copy / ref counting
// reference:
// https://en.cppreference.com/w/cpp/algorithm/copy
//
// interesting read: 
// performance comparison between std::copy and memcpy()
// https://stackoverflow.com/questions/4707012/is-it-better-to-use-stdmemcpy-or-stdcopy-in-terms-to-performance
// 
// the conclusion is to use std::copy()

#include <list>
#include <set>
#include <cassert>

// this is the case where memcpy can not work
void test_copy_non_contiguous_data() {
    std::set<double> src{3, 0, 14, 1, 59, 26, 5, 35, -8, -97};
    std::list<double> dest(10);

    // set iterator provides the source elements in sorted order
    std::copy(src.cbegin(), src.cend(), dest.begin());
    assert(-97 == dest.front());
    assert(59 == dest.back());
}

int main() {
    test_copy_non_contiguous_data();
    return 0;
}
