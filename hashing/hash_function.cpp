//
// Created by wein on 1/4/18.
// 
// this file is re-formated as a test to verify that clang-format and 
// vscode can work together
// source:
// https://code.visualstudio.com/docs/languages/cpp
// https://clang.llvm.org/docs/ClangFormatStyleOptions.html

#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>

int hashf(float v) {
    int i;
    auto n = std::frexp(v, &i);
    return (int)(n * INT_MAX) + i;
}

int main( int argc, char** argv )
{
    float i{0.0};
    while ( i < 10.0 )
    {
        i += 1.0;
        std::cout << hashf( i ) << std::endl;
    }
    return 0;
}
