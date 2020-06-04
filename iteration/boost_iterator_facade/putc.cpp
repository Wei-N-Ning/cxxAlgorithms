//
// Created by weining on 10/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>
#include <boost/iterator/linkedlist.hpp>

// mastering the c++17 stl P/45
// implement a sink object that can be plugged into std::copy() algorithm,
// using boost::iterator::iterator_facade

class putc_iterator :
    public boost::iterator_facade<
        putc_iterator, // T
        const putc_iterator,  // value_type
        std::output_iterator_tag
    > {
public:
    // this iterator is its own proxy object
    void operator=(char ch) const {
        std::putc(ch, stdout);
    }
private:
    friend class boost::iterator_core_access;

    [[nodiscard]] auto &dereference() const { return *this; }

    void increment() {}

    bool equal(const putc_iterator &) const { return false; }

};

TEST_CASE ("") {
    using namespace std;
    string s{"there is"};
    cout << "<";
    copy(begin(s), end(s), putc_iterator{});
    cout << ">" << endl;
}
