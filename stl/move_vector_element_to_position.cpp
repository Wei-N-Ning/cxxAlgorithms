//
// Created by wein on 18/09/18.
//

//
// 0 1 2 3 4 5 6 7 8 9
//     ----------*

// source
// C++ FAQ P14
// this is can be solved nicely by std::rotate

#include <algorithm>
#include <array>
#include <vector>
#include <cassert>

void RunTinyTests();

void test_slide() {
    std::vector<int> haystack{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //                                    >        <
    size_t from_index = 4;
    size_t to_index = 7;
    std::rotate(
        haystack.begin() + from_index,
        haystack.begin() + to_index,
        haystack.begin() + to_index + 1);

    std::array<int, 10> expected{0, 1, 2, 3, 7, 4, 5, 6, 8, 9};
    bool success = std::equal(haystack.cbegin(), haystack.cend(), expected.begin());

    assert(success);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}