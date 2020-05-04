//
// Created by weining on 4/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <complex>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>

// c++ stl cookbook P/241
// source code:
// https://github.com/PacktPublishing/Cpp17-STL-Cookbook/blob/master/Chapter06/mandelbrot.cpp
// Z0 = 0
// Zn+1 = Zn ^ 2 + C
// the variables Z and C are complex numbers. The Mandelbrot set consists of all
// such values of C for which the formula converges if it is applied often enough.
// this is colored part of the poster.
// Some values converge earlier, some converge later, so they can be visualized
// with different colors.
// Some do not converge at all - these are painted black

using cmplx = std::complex<double>;

// to convert integer coordinates to complex-typed coordinates
auto scaler(int min_from, int max_from, double min_to, double max_to) {
    const int w_from{max_from - min_from};
    const double w_to{max_to - min_to};
    const int mid_from{(max_from - min_from) / 2 + min_from};
    const double mid_to{(max_to - min_to) / 2.0 + min_to};

    return [=](int from) {
        return double(from - mid_from) / w_from * w_to + mid_to;
    };
}

template<typename A, typename B>
auto scaled_cmplx(A scaler_x, B scaler_y) {
    return [=](int x, int y) {
        return cmplx{scaler_x(x), scaler_y(y)};
    };
}

auto mandelbrot_iterations(cmplx c) {
    cmplx z{};
    size_t iterations{0};
    const size_t max_iterations{1000};
    while (abs(z) < 2 && iterations < max_iterations) {
        ++iterations;
        z = pow(z, 2) + c;
    }
    return iterations;
}

void gen(int w, int h) {
    auto scale(scaled_cmplx(
        scaler(0, w, -2.0, 1.0),
        scaler(0, h, -1.0, 1.0)
    ));

    // in order to have a one-dimensional iteration over the whole image,
    // we write another transformation function that accepts a one-dimensional
    // i coordinate. It calculates (x, y) coords from that, based on our
    // assumed line of characters width.
    // after breaking i down to the row and column numbers, it transforms
    // them with our scale function and returns the complex coordinate
    auto i_to_xy = [=](int i) {
        return scale(i % w, i / w);
    };

    // transform from 1d coords (the int type), via 2d coords (int, int)
    // to mandelbrot set coords (the cmplx type), and then calculate the
    // number of iterations from there
    auto to_iteration_count = [=](int i) {
        return mandelbrot_iterations(i_to_xy(i));
    };

    // the canvas
    std::vector<int> v(w * h);
    // iota
    // https://en.wikipedia.org/wiki/Iota
    // https://en.cppreference.com/w/cpp/algorithm/iota
    std::iota(std::begin(v), std::end(v), 0);
    std::transform(std::cbegin(v), std::cend(v), std::begin(v), to_iteration_count);

    // dump stuffs to the output iterator
    auto binfunc = [w, n{0}](auto output_it, int x) mutable {
        *(++output_it) = (x > 50 ? '*' : ' ');
        if (++n % w == 0) {
            ++output_it = '\n';
        }
        return output_it;
    };
    std::accumulate(
        std::cbegin(v), std::cend(v),
        std::ostream_iterator<char>{std::cout},
        binfunc
    );
}

TEST_CASE ("") {
    std::cout << std::endl;
    gen(50, 20);  // 10 : 4
    std::cout << std::endl;
}
