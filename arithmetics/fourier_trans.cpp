//
// Created by weining on 4/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

// c++ stl cookbook P/229
// fourier transformation using high level STL constructs

#include <boost/range/irange.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>

#include <complex>
#include <vector>
#include <algorithm>

using cmplx = std::complex<double>;
using csignal = std::vector<cmplx>;
using range = boost::integer_range<int>;

csignal fourier_transform(const csignal &s, bool back = false) {
    csignal t(s.size());
    const double pol{2.0 * M_PI * (back ? -1.0 : 1.0)};
    const double div{back ? 1.0 : double(s.size())};

    auto sum_up = [=, &s](std::size_t j) {
        return [=, &s](cmplx c, std::size_t k) {
            return c + s[k] *
                       std::polar(1.0, pol * k * j / double(s.size()));
        };
    };

    auto to_ft = [=, &s](std::size_t j) {
        return boost::accumulate(
            range(0, s.size()), cmplx{}, sum_up(j)) / div;
    };

    // P/232
    // NONE of the fourier code has been executed until this point
    // we only prepared a lot of functional code (lazy eval)

    // kick start the computation
    boost::transform(range(0, s.size()), std::begin(t), to_ft);
    return t;
}

auto gen_cosine(std::size_t period_len) {
    return [period_len, n = 1]() mutable {
        return cos(double(n++) * 2.0 * M_PI / period_len);
    };
}

auto gen_square_wave(std::size_t period_len) {
    return [period_len, n = period_len * 7 / 4]() mutable {
        return ((n++ * 2 / period_len) % 2) * 2 - 1.0;
    };
}

template<typename F>
csignal signal_from_generator(std::size_t len, F gen) {
    csignal r(len);
    std::generate(std::begin(r), std::end(r), gen);
    return r;
}

void print_signal(const csignal &s) {
    std::transform(
        std::begin(s), std::end(s),
        std::ostream_iterator<double>{std::cout, " "},
        [](auto &c) {
            return c.real();
        }
    );
    std::cout << std::endl;
}

TEST_CASE ("test range") {
    std::vector<int> v;
    boost::range::copy(range(1, 10), std::back_inserter(v));
        CHECK_EQ(9, v.size());
}

TEST_CASE ("test signal") {
    const std::size_t sig_len{100};
    auto cosine{
        signal_from_generator(
            sig_len,
            gen_cosine(sig_len / 2))
    };
    auto square_wave{
        signal_from_generator(
            sig_len,
            gen_square_wave(sig_len / 2))
    };

    auto trans_sqw{fourier_transform(square_wave)};

    std::fill(
        std::next(std::begin(trans_sqw), 10),
        std::prev(std::end(trans_sqw), 10),
        0
    );

    auto mid{fourier_transform(trans_sqw, true)};

    print_signal(cosine);
    print_signal(fourier_transform(cosine));

    print_signal(mid);
    print_signal(trans_sqw);

    print_signal(square_wave);
    print_signal(fourier_transform(square_wave));
}
