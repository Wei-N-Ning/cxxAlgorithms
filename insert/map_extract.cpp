//
// Created by weining on 3/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// c++ stl cookbook P/67
// see:
// https://en.cppreference.com/w/cpp/container/map/extract
// std::move() is a good companion to extract()

#include <map>
#include <algorithm>

TEST_CASE ("") {
    std::map<std::string, size_t> m{
        {"e1m1", 3},
        {"e1m2", 13},
        {"e1m3", 18},
        {"demo", 4},
    };
    auto node_e1m1{m.extract("e1m1")};
    auto node_demo{m.extract("demo")};
    // m["e1m1"] -> returns the default-constructed value
    std::swap(node_e1m1.key(), node_demo.key());
    m.insert(std::move(node_e1m1));
    m.insert(std::move(node_demo));
    CHECK_EQ(4, m["e1m1"]);
    CHECK_EQ(3, m["demo"]);

    // fence it against key-miss
    if (auto it = m.find("e3m1"); it != m.end()) {
        auto node{m.extract(it)};
        CHECK(false);
    }
}
