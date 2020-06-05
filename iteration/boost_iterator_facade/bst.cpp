//
// Created by weining on 5/6/20.
//

// explore how to implement a forward-iterator for a binary search tree

// implementing the node iterator
// see: <https://www.boost.org/doc/libs/1_65_0/libs/iterator/doc/iterator_facade.html>
// NOTE:
// because node iter under the hood uses shared pointer, it is important
// to know shared-pointer's equality operator:
// https://stackoverflow.com/questions/5722988/c-shared-ptr-equality-operator

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/iterator/linkedlist.hpp>
#include <memory>
#include <algorithm>
#include <random>
#include <deque>
#include <iostream>
#include <iterator>

// BST implementation copied from tree/simple_bst.cpp
// NOTE:
// the BST iterator does not respect the inorder, meaning that the values
// will be unordered;

template<typename T>
class Node;

template<typename T>
class node_iter
: public boost::iterator_facade<
    node_iter<T>,
    T,
    std::forward_iterator_tag
> {
public:
    node_iter() = default;
    explicit node_iter(std::shared_ptr<Node<T>> n) {
        queue.push_back(n);
    }

private:
    friend class boost::iterator_core_access;

    [[nodiscard]] auto &dereference() const {
        return queue.front()->value;
    }

    void increment() {
        if (queue.empty()) {
            return;
        }
        auto n = queue.front();
        queue.pop_front();
        if (n->left) {
            queue.push_back(n->left);
        }
        if (n->right) {
            queue.push_back(n->right);
        }
    }

    [[nodiscard]] bool equal(const node_iter<T> &other) const {
        auto lhs{queue.empty() ? nullptr : queue.front()};
        auto rhs{other.queue.empty() ? nullptr : other.queue.front()};
        return lhs == rhs;
    }

    std::deque<std::shared_ptr<Node<T>>> queue{};
};

template<typename T>
class Node : public std::enable_shared_from_this<Node<T>> {
public:
    using PNode = std::shared_ptr<Node<T>>;

    friend class node_iter<T>;

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

    node_iter<T> begin() {
        return node_iter<T>(copy());
    }

    node_iter<T> end() {
        return node_iter<T>();
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

TEST_CASE ("create iterator and increment()") {
    auto root{create_tree(3, 9, 9)};
    node_iter ni{root};
    CHECK_EQ(*ni, 9);
    CHECK_EQ(*(++ni), 9);
    CHECK_EQ(*(++ni), 9);
}

TEST_CASE ("iterator range by explicit construct") {
    auto root{create_tree(3, -9, 9)};
    using node_iter = node_iter<int>;
    for (node_iter begin{root}; begin != node_iter{}; ++begin) {
        std::cout << *begin << " ";
    }
    std::cout << std::endl;
}

TEST_CASE ("iterator range via begin(), end() methods") {
    auto root{create_tree(3, -9, 9)};
    for (auto val : *root) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

TEST_CASE ("std::begin() and std::end()") {
    auto root{create_tree(3, -9, 9)};
    std::copy(std::begin(*root), std::end(*root),
        std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
}

TEST_CASE ("STL algorithms") {
    const std::size_t sz = 10000;
    auto root{create_tree(sz, 1, 99)};
    auto sum = std::accumulate(root->begin(), root->end(), 0,
        [](const auto &acc, const auto &elem) {
            return acc + elem;
    });
    std::cout << sum / (double)sz << std::endl;
}
