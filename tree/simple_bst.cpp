//
// Created by weining on 4/6/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <memory>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <iterator>

// inspired by pro tbb P/125, parallel tree traversal
// I want to implement a simplest possible BST and iterator, then test how fast the parallel
// algorithm can run
// there is also a par-tree traversal example in par_stl using Boost's JSON property tree
// the speedup in that example is not bad.

// IMPORTANT:
// I must use public inheritance (using the public keyword)
// emphasized here (in the example section): https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
// also reported here: https://stackoverflow.com/questions/45210772/stdbad-weak-ptr-exception-when-using-shared-from-this/45211281
template<typename T>
class Node : public std::enable_shared_from_this<Node<T>> {
public:
    using PNode = std::shared_ptr<Node<T>>;

    explicit Node(T val) : value{val} {}

    PNode insert(T val) {
        if (val < value) {
            if (!left) {
                left = std::make_shared<Node<T>>(val);
                return left;
            } else {
                return left->insert(val);
            }
        } else {
            if (!right) {
                right = std::make_shared<Node<T>>(val);
                return right;
            } else {
                return right->insert(val);
            }
        }
    }

    template<typename F>
    void dfs(F f) {
        if (left) {
            left->dfs(f);
        }
        f(value);
        if (right) {
            right->dfs(f);
        }
    }

    PNode copy() {
        return this->shared_from_this();
    }

private:
    T value;
    PNode left{nullptr};
    PNode right{nullptr};
};

template<typename T>
std::shared_ptr<Node<T>> create_tree(std::size_t sz, T mi, T mx) {
    std::default_random_engine engine(std::random_device{}());
    std::uniform_int_distribution<T> dist(mi, mx);
    auto root{std::make_shared<Node<T>>(dist(engine))};
    for (int i = 0; i < sz - 1; ++i) {
        root->insert(dist(engine));
    }
    return root;
}

TEST_CASE ("insert values to binary search tree") {
    const std::size_t sz = 100;
    std::vector<int> vec(sz, 1);
    Node root{vec[0]};
    std::for_each(
        std::next(std::begin(vec), 1), std::end(vec),
        [&root](const auto &v) {
            root.insert(v);
        }
    );
    int counter{0};
    root.dfs([&counter](auto &_) {
        counter++;
    });
    CHECK_EQ(counter, sz);
}

TEST_CASE ("dfs pre-order") {
    const std::size_t sz = 100;
    auto root{create_tree(sz, -0xFFFF, 0xFFFF)};
    std::vector<int> o_vec;
    o_vec.reserve(sz);
    auto it = std::back_inserter(o_vec);
    root->dfs([&it](auto &val) {
        it++ = val;
    });
    CHECK_EQ(std::size(o_vec), sz);
    std::vector<int> o_vec_sorted(o_vec);
    std::sort(std::begin(o_vec_sorted), std::end(o_vec_sorted));
    CHECK_EQ(o_vec, o_vec_sorted);
}

TEST_CASE ("resource life time management") {
    auto node{create_tree(10, -0xFFFF, 0xFFFF)};
    CHECK_EQ(1, node.use_count());
    {
        auto n2 = node->copy();
        CHECK_EQ(2, n2.use_count());
    }
    CHECK_EQ(1, node.use_count());
}
