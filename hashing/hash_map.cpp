//
// Created by weining on 3/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <array>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

// c++ stl cookbook P/69
// how to support a custom, non-trivially-hashable struct in std::unordered_map

struct Weapon {
    std::string name{};
    std::size_t code{};

    bool operator==(const Weapon &other) const {
        return this->name == other.name && this->code == other.code;
    }
};

namespace std {
    template<>
    struct hash<Weapon> {
        using argument_type = Weapon;
        using result_type = size_t;

        result_type operator()(const argument_type &w) const {
            return std::hash<std::string>()(w.name) + std::hash<size_t>()(w.code);
        }
    };
}

TEST_CASE ("") {
    std::unordered_map<Weapon, std::vector<int>> um{
        {{"pistol", 1001}, {1,  2,  3,  4}},
        {{"sks",    3001}, {10, 20, 30, 40}},
    };

    if (auto[it, ok] = um.try_emplace({"mp5", 2001}); ok) {
        CHECK(true);
        it->second.emplace_back(4);
    } else {
        CHECK(false);
    }
}