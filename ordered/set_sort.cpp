//
// Created by weining on 3/5/20.
//

#include <iterator>
#include <string>
#include <set>
#include <iostream>

// c++ stl cookbook P/73
// effective use of i/o iterator and set to implement Unix sort/uniq command

int main() {
    std::set<std::string> s;
    // template parameter can be any type that is possible to write cin >> var
    std::istream_iterator<std::string> it{std::cin};
    std::istream_iterator<std::string> end{};
    copy(it, end, std::inserter(s, s.end()));
    copy(s.cbegin(), s.cend(), std::ostream_iterator<std::string>{std::cout, " "});
    std::cout << std::endl;
    return 0;
}
