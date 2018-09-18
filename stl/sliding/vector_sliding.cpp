//
// Created by wein on 18/09/18.
//

//
// 0 1 2 3 4 5 6 7 8 9
//        |------*
// to slide 7 to the position before 4

// source
// C++ FAQ P14
// this is can be solved nicely by std::rotate
// the term for this pattern is "slide" as explained in the chapter in
// this book "generic slide function"


#include <algorithm>
#include <vector>
#include <cassert>

void RunTinyTests();

void test_slide_one_element() {
    std::vector<int> haystack{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //                                    >        <

    // low to high
    size_t from_index = 4;
    size_t to_index = 7;
    std::rotate(
        haystack.begin() + from_index,
        haystack.begin() + to_index,
        haystack.begin() + to_index + 1);

    std::vector<int> expected{0, 1, 2, 3, 7, 4, 5, 6, 8, 9};
    bool success = std::equal(
        haystack.cbegin(),
        haystack.cend(),
        expected.begin());

    assert(success);

    // high to low
    haystack = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    from_index = 7;
    to_index = 4;

    std::rotate(
        haystack.begin() + from_index,
        haystack.begin() + to_index,
        haystack.begin() + to_index + 1);

    expected = {0, 1, 2, 3, 7, 4, 5, 6, 8, 9};
    success = std::equal(
        haystack.cbegin(),
        haystack.cend(),
        expected.begin());

    assert(success);
}

// Note the use of "numElements" instead of hardcoding it to 1
void test_slide_multiple_elements() {
    std::vector<int> haystack{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //                             |------*******

    size_t from_index = 4;
    size_t to_index = 2;
    size_t numElements = 3;
    std::rotate(
        haystack.begin() + to_index,
        haystack.begin() + from_index,
        haystack.begin() + from_index + numElements
        );

    std::vector<int> expected{0, 1, 4, 5, 6, 2, 3, 7, 8, 9};
    bool success = std::equal(
        haystack.cbegin(),
        haystack.cend(),
        expected.begin());

    assert(success);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}