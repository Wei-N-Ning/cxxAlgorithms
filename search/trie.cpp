//
// Created by weining on 4/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <map>
#include <string>
#include <optional>
#include <vector>
#include <iostream>
#include <functional>

// c++ stl cookbook P/221
// this leads me to some experiments with optional and reference_wrapper in cxxTemplate/references
// see the reasoning below about mutability
// NOTE:
// there was a bug in find() and cfind();
// - always #include <functional> header, so that the code works on gcc 7 and newer versions, 9.1 etc.
// - pair std::ref with mut ref, and std::cref with immut ref; mutability in this case is derived from the iterator type

template<typename T>
class Trie {
    using MapT = std::map<T, Trie<T>>;
    using IteratorT = typename MapT::iterator;

    // I can also enforce/express the immutability via the interface
    // if a method returns CFoundT, the caller can not retrieve a mutable reference from it
    using CFoundT = std::optional<std::reference_wrapper<const Trie<T>>>;
    using FoundT = std::optional<std::reference_wrapper<Trie<T>>>;

public:
    template<typename It>
    void insert(It it, It end) {
        if (it == end) {
            return;
        }
        tries[*it].insert(std::next(it), end);
    }

    template<typename Container>
    void insert(Container &&c) {
        insert(c.begin(), c.end());
    }

    template<typename Elem>
    void insert(std::initializer_list<Elem>&& il) {
        insert(std::begin(il), std::end(il));
    }

    IteratorT begin() noexcept {
        return tries.begin();
    }

    IteratorT end() noexcept {
        return tries.end();
    }

    // NOTE: mutability is controlled by the caller
    FoundT find(T &&word) {
        if (auto it = tries.find(word); it != std::end(tries)) {
            return std::ref(it->second);
        }
        return {};
    }

    // immutability is enforced
    CFoundT cfind(T &&word) {
        if (auto it = tries.find(word); it != std::end(tries)) {
            return std::cref(it->second);
        }
        return {};
    }

    void dump(std::ostream &os, size_t ind_size = 0) const {
        std::string ind(ind_size * 4, ' ');
        for (const auto &[prefix, trie] : tries) {
            os << ind << prefix << std::endl;
            trie.dump(os, ind_size + 1);
        }
    }

private:
    MapT tries{};
};

template<typename T>
class TT;

TEST_CASE ("insert") {
    Trie<std::string> t{};
    t.insert(std::vector<std::string>{"there", "is", "a", "cow"});
    t.insert({"there", "is", "a", "silence"});
    t.insert({"there", "is", "no", "spoon"});

    // to retrieve a mutable reference, use find() instead of cfind()
    if (auto found = t.cfind("there"); found.has_value()) {
        const Trie<std::string> &v = found.value();
    } else {
        CHECK(false);
    }

    if (auto found = t.find("there"); found.has_value()) {
        Trie<std::string> &v = found.value();
        v.insert(std::vector<std::string>{"e1m1", "needs", "iddqd"});
    } else {
        CHECK(false);
    }

}
