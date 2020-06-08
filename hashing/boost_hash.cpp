//
// Created by weining on 8/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/functional/hash.hpp>
#include <string>
#include <vector>

// c++ boost app dev P/253
// string-comparison is slow; int comparison (hash comparison) is fast

template<typename T1, typename T2>
bool is_identical(const T1 &lhs, const T2 &rhs) {
    // NOTE this can not be replaced by std::hash, because the latter only implements the hash function for the
    // primitive types. see:
    // https://en.cppreference.com/w/cpp/utility/hash
    // template<> struct hash<bool>;
    //template<> struct hash<char>;
    //template<> struct hash<signed char>;
    //template<> struct hash<unsigned char>;
    //template<> struct hash<char8_t>;        // C++20
    //template<> struct hash<char16_t>;
    //template<> struct hash<char32_t>;
    //template<> struct hash<wchar_t>;
    //template<> struct hash<short>;
    //template<> struct hash<unsigned short>;
    //template<> struct hash<int>;
    //template<> struct hash<unsigned int>;
    //template<> struct hash<long>;
    //template<> struct hash<long long>;
    //template<> struct hash<unsigned long>;
    //template<> struct hash<unsigned long long>;
    //template<> struct hash<float>;
    //template<> struct hash<double>;
    //template<> struct hash<long double>;
    //template<> struct hash<std::nullptr_t>; // C++17
    //template< class T > struct hash<T*>;
    return boost::hash<T1>()(lhs) == boost::hash<T2>()(rhs);
    // std::hash is provided by header: #include <functional>
//    return std::hash<T1>()(lhs) == std::hash<T2>()(rhs);
}

TEST_CASE ("fast comparison") {
    std::string s1{"iddqd"}, s2{"IDDQD"}, s3{"iddqd"};
    std::vector<int> v1{1, 2, 3};
    CHECK(is_identical(s1, s3));
    CHECK_FALSE(is_identical(v1, s3));

    CHECK(is_identical(1, 1));
    CHECK_FALSE(is_identical(1, 1.0));
}
