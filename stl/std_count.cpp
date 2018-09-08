//
// Created by wein on 8/9/18.
//

// source
// https://en.cppreference.com/w/cpp/algorithm/count
// inspired by more exception item 11, mastermind

#include <algorithm>
#include <map>
#include <deque>
#include <utility>
#include <cassert>

using namespace std;

static map<int, double> s_values{
    {-1, 0.12},
    {2, 0.23},
    {-14, 0.2331},
    {13, 0.1},
};

static deque<int> s_q(10, 1);

// invoke value comparison
void test_count() {
    ssize_t v = count(s_q.cbegin(), s_q.cend(), 1);
    assert(10 == v);
}

// invoke the predicate lambda function
// note the use of const iters and const refs; also note the "side
// effect" - it counts the number of elements that fail the predicate
// test taking advantage of the by-reference capture mode
void test_count_if() {
    int numNegatives = 0;
    ssize_t v = count_if(
        s_values.cbegin(),
        s_values.cend(),
        [&](const pair<int, double>& elem) {
            if (elem.first > 0) {
                return true;
            }
            numNegatives++;
            return false;
        }
    );
    assert(2 == v);
    assert(2 == numNegatives);
}

int main() {
    test_count();
    test_count_if();
    return 0;
}