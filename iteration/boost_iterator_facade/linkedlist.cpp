//
// Created by weining on 5/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/iterator/linkedlist.hpp>
#include <memory>

// master c++ stl P/33
// boost iterator facade to reduce boilerplate code
// source code:
// https://github.com/PacktPublishing/Mastering-the-Cpp17-STL/blob/master/Chapter02/examples-ch2.cc

// UPDATE:
// c++ template: complete guide L17507 explains the facade pattern in 
// details using iterator_facade as a case study

// UPDATE:
// update this example to:
// - turn list node class to a template to support an arbitrary type T
// - use std::shared_ptr for better memory management
// - update the iterator class accordingly

template<typename T>
struct list_node;

template<typename T>
using PNode = std::shared_ptr<list_node<T>>;

template<typename T>
struct list_node {
    T data;
    PNode<T> next;

    list_node(T v, PNode<T> next_): data{v}, next{next_} {}
};

template<typename T>
class list_of_ints;

template<typename T, bool Const>
class list_of_ints_iterator : public boost::iterator_facade<
    list_of_ints_iterator<T, Const>,
    std::conditional_t<Const, const int, int>,
    std::forward_iterator_tag> {
    friend class boost::iterator_core_access;

    friend class list_of_ints<T>;

    friend class list_of_ints_iterator<T, !Const>;

    using node_pointer = std::conditional_t<Const, const PNode<T>, PNode<T>>;
    node_pointer ptr_;

    explicit list_of_ints_iterator(node_pointer p) : ptr_(p) {}

    [[nodiscard]] auto &dereference() const { return ptr_->data; }

    void increment() { ptr_ = ptr_->next; }

    // Support comparison between iterator and const_iterator types
    template<bool R>
    bool equal(const list_of_ints_iterator<T, R> &rhs) const { return ptr_ == rhs.ptr_; }

public:
    // Support implicit conversion of iterator to const_iterator (but not vice versa)
    explicit operator list_of_ints_iterator<T, true>() const { return list_of_ints_iterator<T, true>{ptr_}; }
};

template<typename T>
class list_of_ints {
    PNode<T> head_{nullptr};
    PNode<T> tail_{nullptr};
    std::size_t size_{0};
public:
    using const_iterator = list_of_ints_iterator<T, true>;
    using iterator = list_of_ints_iterator<T, false>;

    list_of_ints() = default;
    list_of_ints(std::initializer_list<T> &&il) {
        std::for_each(std::begin(il), std::end(il), [this](auto &v) { this->push_back(v); });
    }

    // Begin and end member functions
    iterator begin() { return iterator{head_}; }

    iterator end() { return iterator{nullptr}; }

    // nodiscard?
    // https://en.cppreference.com/w/cpp/language/attributes/nodiscard
    // If a function declared nodiscard or a function returning an enumeration or class
    // declared nodiscard by value is called from a discarded-value expression other than a
    // cast to void, the compiler is encouraged to issue a warning.
    [[nodiscard]] const_iterator begin() const { return const_iterator{head_}; }

    [[nodiscard]] const_iterator end() const { return const_iterator{nullptr}; }

    // Other member operations
    [[nodiscard]] std::size_t size() const { return size_; }

    void push_back(T value) {
        PNode<T> new_tail = std::make_shared<list_node<T>>(value, nullptr);
        if (tail_) {
            tail_->next = new_tail;
        } else {
            head_ = new_tail;
        }
        tail_ = new_tail;
        size_ += 1;
    }
};

TEST_CASE ("create list_of_ints and push a new element") {
    list_of_ints<int> li;
    li.push_back(1);
}

TEST_CASE ("range-based for loop") {
    list_of_ints<int> li{1, 1, 1, 1};

    for (auto &v : li) {
        CHECK_EQ(1, v);
    }
    for (const auto &v : li) {
        CHECK_EQ(1, v);
    }
}
