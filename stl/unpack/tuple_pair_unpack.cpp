#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <utility>
#include <string>
#include <tuple>

// inspired by c++17 stl cookbook P/13

TEST_CASE ("unpack pair") {
    using namespace std;
    pair<int, string> p{1, "one"};
    auto &[value, name] = p;
    CHECK_EQ(value, 1);
    CHECK_EQ(name, string{"one"});
    value = 10;
    CHECK_EQ(p.first, 10);
}

TEST_CASE ("unpack tuple") {
    using namespace std;

    tuple<string, size_t, string> p{"e1m1", 32, "hell's gate"};
    const auto &[name, sz, desc] = p;
    CHECK_EQ(name, string{"e1m1"});
    CHECK_EQ(sz, 32);
    CHECK_EQ(desc, string{"hell's gate"});
}