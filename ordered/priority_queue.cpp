//
// Created by weining on 3/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <queue>
#include <algorithm>
#include <tuple>
#include <iostream>

// c++ stl cookbook P/93
// to implement a simple to-do list
//

enum class Category {
    Dev = 1,
    Fix = 3,
    Meeting = 10,
    OneOne = 5,
};

using Item = std::tuple<Category, std::string>;
using TodoList = std::priority_queue<Item>;

TEST_CASE ("") {
    TodoList tl;
    tl.push({Category::Dev, "SPD-856"});
    tl.push({Category::Meeting, "sprint planning"});
    tl.push({Category::Fix, "BUG-131"});
    tl.push({Category::Dev, "SPD-1313"});
    tl.push({Category::OneOne, "Dave K."});

    while (!tl.empty()) {
        const auto &item = tl.top();
        std::cout << std::get<1>(item) << std::endl;
        tl.pop();
    }
}
