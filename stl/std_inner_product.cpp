//
// Created by wein on 8/11/18.
//

// source
// https://en.cppreference.com/w/cpp/algorithm/inner_product

// initializes the accumulator <acc> with the initial value <init>
// and then:
// acc = acc + (*first1) * (*first2)
// then modifies again with:
// acc = acc + *(first1 + 1) * *(first2 + 1)
// so on and so forth...
// until reaching <last1>

// with binary operators
// acc = op1(acc, op2(*first1, *first2))
// acc = op1(acc, op2(*(first1 + 1), *(first2 + 1)))
// so on and so forth...
// until reaching <last1>

// in more exception item 11, masterbind, it employs the second form with
// binary ops
// in that case, op1, the accumulator, is std::plus
// op2, the multiplier, is std::equal_to

// Note, there are some other good gems built around inner_product
// https://marcoarena.wordpress.com/2017/11/14/a-hidden-gem-inner_product/
// https://marcoarena.wordpress.com/2016/09/30/cpp-in-competitive-programming-compromises/

// see also:
// https://www.linkedin.com/pulse/20140814153926-107255014-three-c-11-gems/

#include <iostream>
#include <string>
#include <numeric>

// a common case scenario is I have two sequence of elements and need to
// pick the elements in sequence A and B that match certain criteria,
// such as: both elements have the same color, talk the same language,
// have similar geometric shapes ...
// the second form of std::inner_product() is used, and op2, the
// multiplier, does the matchmaking work
void found_common_characters() {
    std::string strapA{"RBGBAGBRRGBAG"};
    std::string strapB{"AGGRBGRBARBGA"};

    // that accumulator does nothing;
    // the multiplier modifies strapB, taking a mutable ref to its
    // characters
    std::inner_product(strapA.cbegin(), strapA.cend(), strapB.begin(), 0,
        std::plus<>(),
        [](const char& chA, char& chB) -> int {
            if (chA != chB) { chB = '.'; } return 0;
        }
    );

    // TODO: think how can I use this pattern to improve CCI longest
    // common sequence solution??
    std::cout << strapB << std::endl;
}

int main() {
    found_common_characters();
    return 0;
}