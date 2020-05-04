//
// Created by weining on 3/5/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/iterator/zip_iterator.hpp>
#include <list>
#include <vector>
#include <algorithm>

// inspired by c++ stl cookbook P/129
// boost provides its zip iterator utility:
// this example comes from: https://www.boost.org/doc/libs/1_72_0/libs/iterator/doc/zip_iterator.html
// also: https://www.boost.org/doc/libs/1_68_0/libs/iterator/doc/html/iterator/specialized/zip.html#iterator.specialized.zip.zip_reference

// BEWARE:
// - I can combine more than 2 iterators but they become nested tuples. Structural binding won't work
// - the length of both iterators must be identical, otherwise segfault

// UPDATE:
// c++ stl cookbook P/238 introduces a method to compute the pair-wise
// differences of two vectors, using std::inner_product
// this is the case when I don't care of the order of the elements - which is
// different to the scenario of zip_iterator - or only care about the totality
// of the elements
// I categorize this example under permutation/
template<typename T>
class TT;

TEST_CASE ("") {
    std::list<int> l{1, 2, 3, 4};
    std::vector<char> v{'i', 'i', 'i', 'i'};

    std::for_each(
        boost::make_zip_iterator(boost::make_tuple(l.cbegin(), v.cbegin())),
        boost::make_zip_iterator(boost::make_tuple(l.cend(), v.cend())),
        [](const auto &tu) {
            const auto &[id, rest] = tu;
            const auto &[ch] = rest;
            CHECK(id >= 1);
            CHECK_EQ('i', ch);
        }
    );
}
