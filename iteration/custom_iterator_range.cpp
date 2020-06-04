//
// Created by weining on 3/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <vector>
#include <algorithm>
#include <iterator>

// c++ stl cookbook P/107
// how to write an STL compatible custom range-based iterator
// the key is to define the iterator trait specialization for the iterator class

class Range {
public:
    Range() = default;

    Range(int from_, int to_)
        : from{from_}, to{to_}, inc{1} {
        if (from_ > to_) {
            inc = -1;
        }
    }

    int operator*() const {
        return from;
    }

    bool operator==(const Range &other) const {
        return other.from == from;
    }

    bool operator!=(const Range &other) const {
        return other.from != from;
    }

    Range &operator++() {
        if (from != to) {
            from += inc;
        }
        return *this;
    }

    Range begin() {
        return *this;
    }

    [[nodiscard]] Range end() const {
        return Range{to, to};
    }

private:
    int from{0};
    int to{0};
    int inc{0};
};

namespace std {
    template<>
    struct iterator_traits<Range> {
        using iterator_category = std::forward_iterator_tag;
        using value_type = int;
    };
}

TEST_CASE ("range-based for loop and algorithms") {
    std::vector<int> v;
    for (auto n : Range(3, -3)) {
        v.push_back(n);
    }
    for (auto n: Range(-3, 3)) {
        v.push_back(n);
    }
    CHECK_EQ(std::vector<int>{3, 2, 1, 0, -1, -2, -3, -2, -1, 0, 1, 2}, v);

    v.clear();
    std::copy_n(Range(1, 5), 4, std::back_inserter(v));
    CHECK_EQ(std::vector<int>{1, 2, 3, 4}, v);
    Range r{5, 1};
    std::copy(r.begin(), r.end(), v.begin());
    CHECK_EQ(std::vector<int>{5, 4, 3, 2}, v);
}

// c++ stl cookbook P/106
// to make the range class compatible with std::minmax_element function (and other variants), need:
// iterator category
// operator++ returns a reference
TEST_CASE ("STL minmax_element") {
    Range r(3, -3);
    auto [min_it, max_it]{std::minmax_element(std::begin(r), std::end(r))};
    auto min_it_{std::min_element(std::begin(r), std::end(r))};

    CHECK_EQ(-2, *min_it);
}
