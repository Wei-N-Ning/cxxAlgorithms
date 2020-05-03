//
// Created by weining on 3/5/20.
//

// c++ stl P/59
// see:
// https://en.cppreference.com/w/cpp/container/map/try_emplace
/**
 * Unlike insert or emplace, these functions do not move from rvalue arguments
 * if the insertion does not happen, which makes it easy to manipulate maps whose
 * values are move-only types, such as std::map<std::string, std::unique_ptr<foo>>.
 *
 * try_emplace treats the key and the arguments to the mapped_type separately,
 * unlike emplace, which requires the arguments to construct a value_type (that
 * is, a std::pair)
 * */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>
#include <utility>
#include <string>

#include <map>

TEST_CASE ("") {
    using namespace std::literals;
    std::map<std::string, std::string> m;

    m.try_emplace("a", "a"s);
    m.try_emplace("b", "abcd");
    m.try_emplace("c", 10, 'c');
    m.try_emplace("c", "Won't be inserted");

    // using the if-scoped auto variable
    if (auto [it, ok] = m.try_emplace("map", "iddqd"); ok) {
        CHECK_EQ(std::string{"iddqd"}, it->second);
    }
}