//
// Created by wein on 16/03/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <functional>
#include <unordered_map>

template <typename T> T fib(T n) {
  if (n == 0 | n == 1) {
    return n;
  }
  return fib(n - 1) + fib(n - 2);
}

// there is a better example
// https://www.reddit.com/r/cpp/comments/12zw1u/memoization_in_c11/
// explained further here
// http://slackito.com/2011/03/17/automatic-memoization-in-cplusplus0x/
template <typename T> std::function<T(T)> memoize(std::function<T(T)> f) {
  static std::unordered_map<T, T> cache;
  auto g = [&](T n) -> T {
    auto found = cache.find(n);
    if (found == cache.end()) {
      auto computed = f(n);
      cache[n] = computed;
      return computed;
    }
    return found->second;
  };
  return g;
}

TEST_CASE ("test_fib_original()") {
//  fib(37);
//  fib(38);
//  fib(37.0);
//  fib(38.0);
//  fib(37l);
//  fib(38l);
}

TEST_CASE ("test_fib_lookup()") {
  // this awkward cast is needed, and the official reference (cppreference)
  // shows a similar example:
  // https://en.cppreference.com/w/cpp/utility/functional/function
  // NOTE that std::function is a wrapper
  auto g = memoize((std::function<int(int)>)fib<int>);
  g(37);

  // almost no compute cost from here on
  g(38);
  g(37);
  g(38);
  g(37);
  g(38);
  g(38);
  g(38);
  g(38);
  g(38);
  g(38);
}
