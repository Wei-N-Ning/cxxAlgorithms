//
// Created by wein on 5/23/18.
//
// source:
// http://en.cppreference.com/w/cpp/language/const_cast

#include <cassert>
#include <cstring>

void test_constCast() {
    char str[16] = {'t', 'h', 'i', 's', 0};
    const char *s = str;

    // this won't compile
    // s[2] = 'u';
    const_cast<char *>(s)[2] = 'u';
    assert(0 == strcmp(str, "thus"));
}

int main() {
    test_constCast();
    return 0;
}