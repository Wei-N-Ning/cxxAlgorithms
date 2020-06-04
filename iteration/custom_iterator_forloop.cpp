//
// Created by weining on 3/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// c++ stl cookbook P/101
// build your own iterable range and use it in a for-loop

/**
 * for (auto x : range) { code block; }
 *
 * will be evaluated by the compiler to the following:
 *
 * {
 *   auto __begin = std::begin(range);
 *   auto __end = std::end(range);
 *   for (; __begin != __end; ++__begin) {
 *     auto x = *__begin;
 *     code block;
 *   }
 * }
 * */

#include <vector>
#include <algorithm>

struct Iter {
    size_t until{0};

    Iter() = default;
    explicit Iter(size_t v): until(v) {}

    void operator++() {
        if (until != 0) until--;
    }

    bool operator==(const Iter &other) const {
        return this->until == other.until;
    }

    bool operator!=(const Iter &other) const {
        return !operator==(other);
    }

    size_t operator*() {
        return 101;
    }

    // the above code enables the user of Iter to write traditional
    // index-based for loop

    Iter begin() {
        return *this;
    }

    Iter end() {
        return Iter{};
    }

    // with the above code one can write range-based for-loop with Iter
};

TEST_CASE ("") {
    size_t i = 0;
    for (Iter it{3}; it != Iter{}; ++it, ++i) {
        CHECK_EQ(101, *it);
    }
    CHECK_EQ(3, i);

    i = 0;
    for (auto n : Iter{3}) {
        CHECK_EQ(101, n);
        i++;
    }
    CHECK_EQ(3, i);

    // Iter class is not compatible with STL yet
    std::vector<size_t> v(3,0);
    //std::copy(Iter{3}, Iter{}, v.begin());
    //CHECK_EQ(std::vector<size_t>{101, 101, 101}, v);
    // see custom_iterator_range.cpp
}
