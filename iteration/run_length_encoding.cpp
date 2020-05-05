//
// Created by weining on 5/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>
#include <algorithm>
#include <utility>
#include <iterator>
#include <sstream>
#include <numeric>

// c++ stl cookbook P/259
// the example provides a elegant RLE decoding solution

// this is my hack
std::string RLE(const std::string &s) {
    std::pair<char, int> record{s.front(), 0};
    std::ostringstream oss{};
    std::for_each(s.cbegin(), s.cend(),
                  [&record, &oss](const auto &ch) {
                      if (record.first == ch) {
                          record.second++;
                      } else {
                          oss << record.first << record.second;
                          record.first = ch;
                          record.second = 1;
                      }
                  });
    oss << record.first << record.second;
    return oss.str();
}

// this is from the book
std::string RLD(const std::string &s) {
    std::stringstream ss{s};
    std::stringstream r;
    char c;
    std::size_t n;
    while (ss >> c >> n) {
        r << std::string(n, c);
    }
    return r.str();

}

TEST_CASE ("") {
    std::string s{"tttthheereeeiiiissaaacooooww"};
    std::cout << RLE(s) << std::endl;
    CHECK_EQ(std::string{"i1d2q1d1"}, RLE("iddqd"));
    CHECK_EQ(std::string{"iddqd"}, RLD("i1d2q1d1"));
    CHECK_EQ(s, RLD(RLE(s)));
}
