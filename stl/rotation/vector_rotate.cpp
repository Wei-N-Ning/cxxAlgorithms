//
// Created by wein on 18/09/18.
//

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <sstream>

// source
// https://en.cppreference.com/w/cpp/algorithm/rotate
// void rotate( ForwardIt first, ForwardIt n_first, ForwardIt last );
// Specifically, std::rotate swaps the elements in the range [first, last)
// in such a way that the element n_first becomes the first element of
// the new range and n_first - 1 becomes the last element.

template<typename Elem>
static std::string spprint(const std::vector<Elem>& v, const char* delimiter) {
    if (! v.empty()) {
        std::stringstream ss;
        std::copy(v.cbegin(), v.cend() - 1, std::ostream_iterator<Elem>(ss, delimiter));
        ss << v.back();
        return ss.str();
    }
    return {};
}

template<typename Elem>
static void pprint(const std::vector<Elem>& v, const char* delimiter) {
    std::cout << spprint(v, delimiter) << std::endl;
}

void RunTinyTests();

void test_range_of_elements() {
    std::vector<double> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << std::endl;
    pprint(v, ",");

    {
        auto v_ = v;
        std::rotate(v_.begin(), v_.begin() + 4, v_.end());
        pprint(v_, ",");
    }

    {
        auto v_ = v;
        std::rotate(v_.begin(), v_.begin() + 1, v_.end());
        pprint(v_, ",");
    }

    {
        // do nothing
        auto v_ = v;
        std::rotate(v_.begin(), v_.begin(), v_.end());
        pprint(v_, ",");
    }

    {
        // do nothing
        auto v_ = v;
        std::rotate(v_.begin(), v_.end(), v_.end());
        pprint(v_, ",");
    }

}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}