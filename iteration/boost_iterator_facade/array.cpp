//
// Created by weining on 5/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/iterator/linkedlist.hpp>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

// continue the path in linkedlist.cpp, explore the resource management
// aspect when using iterators
// it also explores:
// - the complete list of methods to impl
//   accordingly to https://www.boost.org/doc/libs/1_72_0/libs/iterator/doc/facade-and-adaptor.html
// - use this block_iterator in STL and custom algorithms (copy and qsort)
// - mutability

template<typename T,
    typename Alloc,
    template<typename, typename> typename Container
>
class block_iterator
    : public boost::iterator_facade<
        block_iterator<T, Alloc, Container>,
        T,
        std::random_access_iterator_tag
    > {
public:
    explicit block_iterator(Container<T, Alloc> &container, std::size_t pos = 0)
    : ctn(&container), position{pos} {}

private:
    friend class boost::iterator_core_access;

    [[nodiscard]] auto &dereference() const {
        return (*ctn)[position];
    }

    void increment() {
        ++position;
    }

    void decrement() {
        --position;
    }

    [[nodiscard]]
    typename block_iterator<T, Alloc, Container>::difference_type
    distance_to(const block_iterator<T, Alloc, Container> &other) const {
        return other.position - position;
    }

    void advance(std::size_t n) {
        position += n;
    }

    bool equal(const block_iterator<T, Alloc, Container> &other) {
        return ctn == other.ctn && position == other.position;
    }

    Container<T, Alloc> *ctn{nullptr};
    std::size_t position{0};
};

// this is to demonstrate the potential resource life time violation:
// if the resource (the scoped vector) goes out of scope, all the iterators
// MUST BE invalidated
// on the other hand, it is NOT the iterator's concern to manage the resource
// life time therefore it can use a plain pointer
TEST_CASE ("resource life time violation") {
    std::vector<int>::iterator first;
    std::vector<int>::iterator last;
    {
        std::vector<int> vec{3, 1, 4, 15, 9, 2, 6};
        first = vec.begin();
        last = vec.end();
    }
    // run with valgrind to show the violation:
    // Invalid write of size 4 (7 errors)
    // std::fill(first, last, 999);
}

template<typename It>
void qsort(It first, It last) {
    auto dis = std::distance(first, last);
    if (dis > 1) {
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

TEST_CASE ("create iterator") {
    std::vector<int> vec{3, 1, 4, 15};
    block_iterator bi{vec};
}

TEST_CASE ("mutability") {
    std::vector<int> vec{3, 1, 4, 15};
    block_iterator bi{vec};
    *bi = 123;
    CHECK_EQ(vec[0], 123);
    int a = 456;
    std::swap(*(++bi), a);
    CHECK_EQ(vec[1], 456);
    CHECK_EQ(a, 1);
}

TEST_CASE ("bidirectional access (and distance_to())") {
    std::vector<int> vec{3, 14, 1, 5, 9, 2};
    block_iterator first{vec};
    block_iterator last{vec, 6};
    qsort(first, last);

    std::vector<int> v;
    std::copy(
        std::begin(vec), std::end(vec),
        std::ostream_iterator<int>{std::cout, " "}
    );
    std::cout << std::endl;
    CHECK_EQ(vec, std::vector<int>{1, 2, 3, 5, 9, 14});
}
