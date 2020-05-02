//
// Created by weining on 2/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cstdlib>
#include <string>

// c++ stl cookbook P/17
// variable p is scoped to the if statement
// a nice feature borrowed from golang IMO

TEST_CASE ("demo if-statement auto variable") {
    // std::getenv
    // https://en.cppreference.com/w/cpp/utility/program/getenv
    if (auto p{std::getenv("HOME")}; p != nullptr) {
        CHECK_NE(std::string{p}.find('/'), std::string::npos);
    } else {
        CHECK(true);
    }

    if (auto p{std::getenv("HOMEDD")}; p != nullptr) {
        CHECK_EQ(std::string{p}.find('/'), std::string::npos);
    } else {
        CHECK(true);
    }

    // homePath is not available
    // CHECK(homePath.empty());
}

enum class Case {
    Red,
    Blue,
};

TEST_CASE ("demo switch-case auto variable") {
    size_t count = 0;
    for (const auto &elem : std::string{"iddqd"}) {
        switch (auto c{elem}; c) {
            case 'i': {
                count += 4;
                break;
            }
            case 'd': {
                count += 10;
                break;
            }
            default: {
                count -= 1;
            }
        }
    }
    CHECK_EQ(33, count);
}
