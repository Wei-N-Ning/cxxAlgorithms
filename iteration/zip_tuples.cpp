//
// Created by weining on 8/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <functional>
#include <tuple>

// c++ stl cookbook P/352
// the art of partial application

// calling apply(f, a) leads to a function call f(1, 2, 3) which returns another
// function object that captures those values 1, 2, 3, in the parameter pack xs
// when this function object is then called with apply(f(1, 2, 3), b), it gets
// the values a b c, stuffed into the parameter pack ys
// this is basically the same as if we called f(1, 2, 3)(a, b, c) directly.
template<typename T1, typename T2>
auto zip(const T1 &a, const T2 &b) {
    auto f = [](auto ...xs) {
        return [xs...](auto ...ys) {
            // at first, items from xs and ys are zipped together by interleaving
            // them pairwise (make_tuple(xs, ys)
            // this initially only leads to a variadic list of tuples with two
            // items each; in order to get one large tuple, we apply
            // tuple_cat() on them and then we finally get a large concatenated
            // tuple that contains all the members of the initial tuples in
            // an interleaved manner
            return std::tuple_cat(std::make_tuple(xs, ys) ...);
        };
    };
    return std::apply(std::apply(f, a), b);
}

TEST_CASE ("") {
    using namespace std;
    auto zz = zip(make_tuple(1, 2, 3), make_tuple('a', 'b', 'c'));
    // zz is of type tuple<int, char, int, char, int, char>

    auto &[l, r, _1, _2, _3, _4] = zz;
    CHECK_EQ(1, l);
    CHECK_EQ('a', r);
}
