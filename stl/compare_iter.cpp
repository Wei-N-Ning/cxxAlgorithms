
#include <iterator>
#include <vector>
#include <cassert>

using V = std::vector<int>;

void RunTinyTests();

void test_equality() {
    V v(10, 0);
    assert(v.cbegin() + 4 == v.end() - 6);
    assert(v.end() == v.cbegin() + v.size());
    assert(v.begin() - 1 != v.end());
}

void test_arithmetic_comparison() {
    V v(10, 0);
    assert(v.begin() < v.cend());
    assert(v.begin() + 39 > v.cend());
    assert(10 == v.end() - v.cbegin());

    int a[8];
    assert(std::begin(a) < std::end(a));
    assert(std::begin(a) + 39 > std::end(a));
    assert(8 == std::end(a) - std::begin(a));
}

int main() {
    RunTinyTests();
    return 0;
}
