#include <numeric>
#include <map>
#include <string>
#include <cassert>

// source
// https://en.cppreference.com/w/cpp/algorithm/accumulate
// inspired by more exception item 11, mastermind game
// see /cases/mastermind for full details

static std::map<std::string, int> s_weapons{
    {"ak47", 12},
    {"akm", 54},
    {"ak47s", 3},
    {"ak74", 34},
    {"ak104", 3},
    {"ak74m", 5},
    {"ak74s", 10},
};

static std::string s_bytes{"\x10\x10\x10\x10"};

// use the first form of std::accumulate()
// this form simply adds the value of each element together
// note the use of initial value
void test_simple() {
    int v = 0;
    v = std::accumulate(s_bytes.cbegin(), s_bytes.cend(), 0);
    assert(0x40 == v);
    v = std::accumulate(s_bytes.cbegin(), s_bytes.cend(), -0x40);
    assert(0 == v);
}

// use the second form of std::accumulate()
// the source data is held in a map therefore the binary op must 
// account for the type of its iterator (including const-ness!!)
// 
// 1st example
// the binary op simply takes the value of each key-value pair and 
// adds it to the sum
//
// 2nd example
// the binary op selectively takes the elements that meet its criteria
// (the weapon is compact) and only adds the value to the sum from 
// such elements; 
// because of the capture mode being by-reference, the lambda function 
// can modify other variables in its parent scope while still produces 
// the sum
// 
// std::basic_string::rfind
// https://en.cppreference.com/w/cpp/string/basic_string/rfind
void test_conditional() {
    int v = 0;
    v = std::accumulate(
        s_weapons.cbegin(), s_weapons.cend(), 0,
        [](int sum, const std::pair<std::string, int>& elem) -> int {
            return sum + elem.second;
        }
    );
    assert(121 == v);
    
    int num_compactWeapons = 0;
    v = std::accumulate(
        s_weapons.cbegin(), s_weapons.cend(), 0,
        [&](int sum, const std::pair<std::string, int>& elem) -> int {
            if (elem.first.rfind("s") == elem.first.size() - 1) {
                num_compactWeapons++;
                return sum + elem.second;
            }
            return sum;
        }
    );
    assert(2 == num_compactWeapons);
    assert(13 == v);
}

int main() {
    test_simple();
    test_conditional();
    return 0;
}
