//
// Created by weining on 3/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <vector>
#include <random>

// https://www.geeksforgeeks.org/heap-sort/
// https://www.geeksforgeeks.org/binary-heap/

template<typename C, typename It>
void heapify(C &ctn, It i) {
    if (ctn.empty) {
        return;
    }
    It largest = i;
    It last = ctn.end() - 1;
    auto dis = std::distance(ctn.begin(), i);
    It l = std::next(i, dis * 2 + 1);
    It r = std::next(i, dis * 2 + 2);
    if (l < last && *l > *largest) largest = l;
    if (r < last && *r > *largest) largest = r;
    if (largest != i) {
        std::swap(*i, *largest);
        heapify(ctn, largest);
    }
}

template<typename C>
void heapsort(C &ctn) {

}

template<typename T, typename RD = std::default_random_engine>
void lazyman_vector(std::vector<T> &o_vec, T mi, T mx) {
    RD rd(std::random_device{}());
    std::uniform_int_distribution<T> dist(mi, mx);
    std::generate(std::begin(o_vec), std::end(o_vec), [&dist, &rd]() { return dist(rd); });
}

TEST_CASE ("") {
    std::vector<int> vec1(100);
    lazyman_vector(vec1, -9999, 9999);
    std::vector<int> vec2{vec1};


}
