//
// Created by weining on 5/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include <string>
#include <vector>
#include <algorithm>

// c++ stl cookbook P/247

// boost split:
// https://www.boost.org/doc/libs/1_72_0/doc/html/string_algo/usage.html#id-1.3.3.5.9
// https://www.boost.org/doc/libs/1_72_0/doc/html/boost/algorithm/split.html

TEST_CASE ("boost split example") {
    using namespace std;
    using find_vector_type = vector<boost::iterator_range<string::iterator>>;
    using split_vector_type = vector<string>;

    string str1("hello abc-*-ABC-*-aBc goodbye");
    find_vector_type FindVec; // #1: Search for separators
    boost::ifind_all(FindVec, str1, "abc"); // FindVec == { [abc],[ABC],[aBc] }
    split_vector_type split_to; // #2: Search for tokens
    split(split_to, str1, boost::is_any_of("-*"), boost::token_compress_on);
    CHECK_EQ(vector<string>{"hello abc", "ABC", "aBc goodbye"}, split_to);
}
