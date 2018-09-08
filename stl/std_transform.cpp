//
// Created by wein on 8/11/18.
//

// source
// seen this function template wkou code base
// also inspired by more exception item 11, mastermind
// reference:
// https://en.cppreference.com/w/cpp/algorithm/transform

#include <algorithm>
#include <vector>
#include <cassert>

void test_one_input_sequence() {
    std::vector<double> samples{1, 2, 3, 4, 5};
    std::vector<double> results(5);
    std::transform(
        samples.cbegin(), samples.cend(),
        results.begin(),
        [](const double& sample) -> double {
        return sample;
    });
    assert(5.0 == results[4]);
}

void test_two_input_sequences() {
    std::vector<double> samples{1, 2, 3, 4, 5};
    std::vector<double> factors{-1, -2, -3, -2, -1};
    std::vector<double> results(5);
    std::transform(
        samples.cbegin(), samples.cend(),
        factors.cbegin(),
        results.begin(),
        [](const double& sample, const double& factor) -> double {
            return sample * 4.0 + factor;
        }
    );
}


int main() {
    test_one_input_sequence();
    test_two_input_sequences();
    return 0;
}