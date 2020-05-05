//
// Created by weining on 5/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include <string>
#include <list>
#include <regex>
#include <iterator>
#include <vector>
#include <algorithm>

// c++ stl cookbook P/247

// boost split:
// https://www.boost.org/doc/libs/1_72_0/doc/html/string_algo/usage.html#id-1.3.3.5.9
// https://www.boost.org/doc/libs/1_72_0/doc/html/boost/algorithm/split.html

// NOTE:
// this example overlaps with cxxString/regex,partition, which focus on the
// string-splitting cases

TEST_CASE ("boost split string example") {
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

// c++ stl cookbook P/251
// this scenario uses two needles
TEST_CASE ("split anything example") {
    using namespace std;
    vector<int> v{1, 2, 2, 1, 33, 2, 1, 10, 2};
    vector<vector<int>> out;
    auto from = v.cbegin();
    auto to = v.cbegin();
    auto end = v.cend();
    while (to != end) {
        to = std::find(from, end, 1);
        if (from != to) {
            vector<int> o{};
            std::copy(from, to, std::back_inserter(o));
            out.push_back(std::move(o));
        }
        from = std::next(to);
    }
    CHECK_EQ(3, out.size());
    for (const auto &s : out) {
        std::copy(s.cbegin(), s.cend(), std::ostream_iterator<int>{cout, " "});
        cout << endl;
    }
}

TEST_CASE ("regex split()") {
    std::string haystack{"there , is , a , cow"};
    std::regex re{R"Re([\s,]+)Re"};
    std::list<std::string> o;
    std::sregex_token_iterator it{haystack.cbegin(), haystack.cend(), re, -1};
    std::sregex_token_iterator end{};
    std::copy(it, end, std::inserter(o, o.end()));
    CHECK_EQ(std::list<std::string>{"there", "is", "a", "cow"}, o);
}
