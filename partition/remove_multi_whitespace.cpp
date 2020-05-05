//
// Created by weining on 5/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <string>
#include <iostream>

// c++ stl cookbook P/254
// see also:
// https://en.cppreference.com/w/cpp/algorithm/unique

TEST_CASE ("") {
    std::string speech{"theeeere iiiis   aaa    ccow"};
    auto it = std::unique(
        speech.begin(), speech.end(),
        [](const auto &fst, const auto &snd) {
            return std::isspace(fst) && std::isspace(snd);
        });
    speech.erase(it, speech.end());
    std::cout << speech << std::endl;
}
