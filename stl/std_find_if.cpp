//
// Created by wein on 8/11/18.
//

// reference:
// https://en.cppreference.com/w/cpp/algorithm/find

#include <algorithm>
#include <vector>
#include <random>
#include <cassert>

// given 100 elements distributed in range (0, 100000),
// assert that there exists at least one element that
// is less or equal to one-tenth of the max value (100000 * 0.1)
void test_random_distribution() {
    constexpr int numElements = 100;
    constexpr int maxValue = 100000;
    std::vector<int> v(numElements);
    std::srand(static_cast<unsigned int>(time(nullptr)));
    std::generate(
        v.begin(),
        v.end(),
        []() -> int {
            return static_cast<int>(random() % maxValue);
        });
    // it's type is std::vector<int>::iterator OR
    // std::vector<const int>::iterator, depending on
    // the input iterator types (begin() or cbegin())
    auto it = std::find_if(
        v.begin(),
        v.end(),
        [](int& elem) -> bool {
            return elem <= (maxValue * 0.1);
        });
    assert(it != v.end());
}

int main() {
    return 0;
}