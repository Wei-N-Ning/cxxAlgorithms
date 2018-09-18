//
// Created by wein on 19/09/18.
//

// source
// C++ FAQ P1

#include <array>
#include <vector>
#include <algorithm>

#include <cassert>

void RunTinyTests();

void test_append_rotate() {
    std::vector<int> haystack{1, 2, 3, 4};
    std::vector<int> needle{-1, -3, -5};

    size_t insert_after_index = 2;
    size_t haystackSize = haystack.size();
    haystack.insert(haystack.end(), needle.cbegin(), needle.cend());
    std::rotate(
        haystack.begin() + insert_after_index + 1,

        haystack.begin() + haystackSize,
        // ---- needle -----
        haystack.end());

    std::array<int, 7> expected{1, 2, 3, -1, -3, -5, 4};
    bool success =
        std::equal(haystack.cbegin(), haystack.cend(), expected.cbegin());

    assert(success);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
