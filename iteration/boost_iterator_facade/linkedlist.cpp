//
// Created by weining on 5/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/iterator/linkedlist.hpp>

// master c++ stl P/33
// boost iterator facade to reduce boilerplate code
// source code:
// https://github.com/PacktPublishing/Mastering-the-Cpp17-STL/blob/master/Chapter02/examples-ch2.cc

// UPDATE:
// c++ template: complete guide L17507 explains the facade pattern in 
// details using iterator_facade as a case study

struct list_node {
    int data;
    list_node *next;
};

template<bool Const>
class list_of_ints_iterator : public boost::iterator_facade<
    list_of_ints_iterator<Const>,
    std::conditional_t<Const, const int, int>,
    std::forward_iterator_tag> {
    friend class boost::iterator_core_access;

    friend class list_of_ints;

    friend class list_of_ints_iterator<!Const>;

    using node_pointer = std::conditional_t<Const, const list_node *, list_node *>;
    node_pointer ptr_;

    explicit list_of_ints_iterator(node_pointer p) : ptr_(p) {}

    [[nodiscard]] auto &dereference() const { return ptr_->data; }

    void increment() { ptr_ = ptr_->next; }

    // Support comparison between iterator and const_iterator types
    template<bool R>
    bool equal(const list_of_ints_iterator<R> &rhs) const { return ptr_ == rhs.ptr_; }

public:
    // Support implicit conversion of iterator to const_iterator (but not vice versa)
    explicit operator list_of_ints_iterator<true>() const { return list_of_ints_iterator<true>{ptr_}; }
};

class list_of_ints {
    list_node *head_ = nullptr;
    list_node *tail_ = nullptr;
    int size_ = 0;
public:
    using const_iterator = list_of_ints_iterator<true>;
    using iterator = list_of_ints_iterator<false>;

    list_of_ints(std::initializer_list<int> &&il) {
        std::for_each(std::cbegin(il), std::cend(il), [this](const auto &v) { this->push_back(v); });
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
    [[nodiscard]] int size() const { return size_; }

    void push_back(int value) {
        auto *new_tail = new list_node{value, nullptr};
        if (tail_) {
            tail_->next = new_tail;
        } else {
            head_ = new_tail;
        }
        tail_ = new_tail;
        size_ += 1;
    }

    ~list_of_ints() {
        for (list_node *next, *p = head_; p != nullptr; p = next) {
            next = p->next;
            delete p;
        }
    }
};

TEST_CASE ("") {
    list_of_ints li{1, 1, 1, 1};
    for (auto &v : li) {
        CHECK_EQ(1, v);
    }
    for (const auto &v : li) {
        CHECK_EQ(1, v);
    }
}

