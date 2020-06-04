//
// Created by weining on 4/6/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <memory>
#include <vector>
#include <random>
#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <boost/iterator/linkedlist.hpp>

// inspired by pro tbb P/125, parallel tree traversal
// I want to implement a simplest possible BST and iterator, then test how fast the parallel
// algorithm can run
// there is also a par-tree traversal example in par_stl using Boost's JSON property tree
// the speedup in that example is not bad.

// implementing the node iterator
// see: <https://www.boost.org/doc/libs/1_65_0/libs/iterator/doc/iterator_facade.html>
// NOTE: because node iter under the hood uses shared pointer, it is important
// to know shared-pointer's equality operator:
// https://stackoverflow.com/questions/5722988/c-shared-ptr-equality-operator

// NOTE: I can't get the iterator part to work
// TODO:
// https://stackoverflow.com/questions/40809926/modelling-an-arbitrary-tree-in-c-with-iterators/40897836
// https://stackoverflow.com/questions/4581576/implementing-an-iterator-over-a-binary-search-tree
// https://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c16121/STL-and-BOOST-Parsing-Iterators.htm

template<typename T>
class NodeIter;

template<typename T>
class Node : std::enable_shared_from_this<Node<T>> {
public:
    using PNode = std::shared_ptr<Node<T>>;
    friend NodeIter<T>;

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

    NodeIter<T> begin() {
        return NodeIter<T>(this->shared_from_this());
    }

    NodeIter<T> end() {
        return NodeIter<T>();
    }

private:
    T value;
    PNode left{nullptr};
    PNode right{nullptr};
};

template<typename T>
class NodeIter
    : public boost::iterator_facade<
        NodeIter<T>,
        Node<T>,
        boost::forward_traversal_tag
    > {
public:
    NodeIter() = default;
    explicit NodeIter(std::shared_ptr<Node<T>> n) {
        queue.push_back(n);
    }

private:
    friend class boost::iterator_core_access;

    void increment() {
        if (!queue.empty()) {
            auto n{queue.front()};
            queue.pop_front();
            if (n->left) {
                queue.push_back(n->left);
            }
            if (n->right) {
                queue.push_back(n->right);
            }
        }
    }

    bool equal(const NodeIter<T> &other) const {
        if (!queue.empty() && !other.queue.empty()) {
            return queue.front() == other.queue.front();
        }
        if (queue.empty() && !other.queue.empty()) {
            return false;
        }
        return !(!queue.empty() && other.queue.empty());
    }

    std::shared_ptr<Node<T>> &dereference() const {
        auto n = queue.front();
        return n;
    }

    std::deque<std::shared_ptr<Node<T>>> queue;
};

template<typename C, typename T>
void populate_vector(C &c, T mi, T mx) {
    std::default_random_engine engine(std::random_device{}());
    std::uniform_int_distribution<T> dist(mi, mx);
    std::generate(std::begin(c), std::end(c), [&dist, &engine]() { return dist(engine); });
}

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
    std::vector<int> vec(10000);
    populate_vector(vec, -0xFFFF, 0xFFFF);
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
        CHECK_EQ(counter, 10000);
}

TEST_CASE ("dfs pre-order") {
    std::vector<int> vec(10);
    populate_vector(vec, -0xFFFF, 0xFFFF);
    Node root{vec[0]};
    std::for_each(
        std::next(std::begin(vec), 1), std::end(vec),
        [&root](const auto &v) {
            root.insert(v);
        }
    );
    std::vector<int> o_vec;
    o_vec.reserve(10);
    auto it = std::back_inserter(o_vec);
    root.dfs([&it](auto &val) {
        it++ = val;
    });
        CHECK_EQ(std::size(o_vec), std::size(vec));

    std::sort(std::begin(vec), std::end(vec));
        CHECK_EQ(o_vec, vec);
}

TEST_CASE ("node iter") {
    auto root{create_tree(3, -999, 999)};
    NodeIter<int> ni{root};
    NodeIter<int> end{};
    CHECK_NE(ni, end);
    ni++; ni++;
    CHECK_NE(ni, end);
    ni++;
    CHECK_EQ(ni, end);
}

TEST_CASE ("use node iter in algorithm") {
    auto root{create_tree(3, -999, 999)};
    for (auto pn = NodeIter(root); pn != root->end(); pn++) {
        ;
    }
}
