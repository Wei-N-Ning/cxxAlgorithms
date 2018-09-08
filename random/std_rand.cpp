
#include "bsd_drand48.hh"

#include <iostream>
#include <random>
#include <cassert>
#include <cstdlib>

// source
// http://www.cplusplus.com/reference/random/
// http://www.cplusplus.com/reference/random/uniform_real_distribution/
//
// motivation:
// raytracer in a weekend chapter 6 P19, antialiasing

// test driver source:
// http://www.cplusplus.com/reference/random/uniform_real_distribution/

using RandomFuncFT = float(*)();
using RandomFuncDT = double(*)();

namespace testing {

int driver(RandomFuncDT df) {
    const int nrolls=10000;  // number of experiments
    const int nstars=95;     // maximum number of stars to distribute
    const int nintervals=10; // number of intervals

    int p[nintervals]={};

    for (int i=0; i<nrolls; ++i) {
        double number = df();
        ++p[int(nintervals*number)];
    }

    std::cout << std::fixed; std::cout.precision(1);

    for (int i=0; i<nintervals; ++i) {
        std::cout <<
            float(i)/nintervals <<
            "-" <<
            float(i+1)/nintervals <<
            ": ";
        std::cout <<
            std::string(std::size_t(p[i] * nstars / nrolls), '*') <<
            std::endl;
    }

    return 0;
}

}

double std_rand_d() {

    //////// gotcha ////////
    //
    // DO NOT recreate the random number generator and distributor
    // every time.
    // They probably belong to a persistent state and need to be
    // initialized only once.
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(0.0,1.0);

    return distribution(generator);
}

void test_linux_drand48() {
    assert(drand48() > 0.0);
    assert(drand48() < 1.0);
}

void test_bsd_drand48() {
    assert(bsd_drand48() > 0.0);
    assert(bsd_drand48() < 1.0);
}

void driver_run() {
    std::cout << "uniform_real_distribution double (0.0,1.0):" << std::endl;
    testing::driver(std_rand_d);

    std::cout << "liunx pseudo drand48() (0.0,1.0):" << std::endl;
    testing::driver(drand48);

    std::cout << "bsd pseudo bsd_drand48() (0.0,1.0):" << std::endl;
    testing::driver(bsd_drand48);
}

int main() {
    assert(std_rand_d() > 0.0);
    assert(std_rand_d() < 1.0);

    test_linux_drand48();
    test_bsd_drand48();

    driver_run();

    return 0;
}
