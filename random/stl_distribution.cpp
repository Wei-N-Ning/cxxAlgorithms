//
// Created by weining on 9/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <map>
#include <random>
#include <algorithm>
#include <string>
#include <iostream>

// c++ stl cookbook P/395
// calling rd (the random engine) alone would get us a raw random number from
// the random engine, dist(rd) shapes the random numbers through the distribution
// object

template<typename T>
void print_dist(T dist, std::size_t samples) {
    std::default_random_engine e;
    std::map<int, std::size_t> m;

    for (std::size_t i = 0; i < samples; ++i) {
        m[dist(e)] += 1;
    }

    auto max_elem = std::max_element(std::cbegin(m), std::cend(m),
        [](const auto &a, const auto &b) {
        return a.second < b.second;
    })->second;

    std::size_t max_div{std::max(max_elem / 100, std::size_t{1})};

    for (const auto [randval, count] : m) {
        if (count < max_elem / 200) {
            continue;
        }
        std::cout << std::setw(3) << randval << ": "
                  << std::string(count / max_div, '*')
                  << std::endl;
    }
}

TEST_CASE ("") {
    using namespace std;
    size_t samples{1000};

    cout << "// uniform_int_distribution" << endl;
    print_dist(uniform_int_distribution<int>{0, 9}, samples);
    cout << endl;

    cout << "// normal_distribution" << endl;
    print_dist(normal_distribution<double>{0.0, 2.0}, samples);
    cout << endl;

    cout << "// piecewise_constant_distribution" << endl;
    std::initializer_list<double> intervals{0, 2, 4, 6};
    std::initializer_list<double> weights{0.1, 0.2, 0.7};
    print_dist(piecewise_constant_distribution<double>{
        begin(intervals), end(intervals), begin(weights)
        }, samples);
    cout << endl;

    cout << "// piecewise_linear_distribution" << endl;
    std::initializer_list<double> weights2{0, 1, 1, 0};
    print_dist(piecewise_linear_distribution<double>{
        begin(intervals), end(intervals), begin(weights2),
        }, samples);
    cout << endl;

    cout << "// bernoulli_distribution" << endl;
    print_dist(bernoulli_distribution{0.75}, samples);
    cout << endl;

    cout << "// discrete_distribution" << endl;
    print_dist(discrete_distribution<int>{{1, 2, 4, 8}}, samples);
    cout << endl;

    cout << "// binomial_distribution" << endl;
    print_dist(binomial_distribution<int>{10, 0.3}, samples);

    cout << endl << "// negative_binomial_distribution" << endl;
    print_dist(negative_binomial_distribution<int>{10, 0.8}, samples);

    cout << endl << "// geometric_distribution" << endl;
    print_dist(geometric_distribution<int>{0.4}, samples);

    cout << endl << "// exponential_distribution" << endl;
    print_dist(exponential_distribution<double>{0.4}, samples);

    cout << endl << "// gamma_distribution" << endl;
    print_dist(gamma_distribution<double>{1.5, 1.0}, samples);

    cout << endl << "// weibull_distribution" << endl;
    print_dist(weibull_distribution<double>{1.5, 1.0}, samples);

    cout << endl << "// extreme_value_distribution" << endl;
    print_dist(extreme_value_distribution<double>{0.0, 1.0}, samples);

    cout << endl << "// lognormal_distribution" << endl;
    print_dist(lognormal_distribution<double>{0.5, 0.5}, samples);

    cout << endl << "chi_squared_distribution" << endl;
    print_dist(chi_squared_distribution<double>{1.0}, samples);

    cout << endl << "cauchy_distribution" << endl;
    print_dist(cauchy_distribution<double>{0.0, 0.1}, samples);

    cout << endl << "fisher_f_distribution" << endl;
    print_dist(fisher_f_distribution<double>{1.0, 1.0}, samples);

    cout << endl << "student_t_distribution" << endl;
    print_dist(student_t_distribution<double>{1.0}, samples);
}
