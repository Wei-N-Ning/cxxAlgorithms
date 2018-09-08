
// source
// inspired by more exception item 11, masterpiece
// reference:
// https://en.cppreference.com/w/cpp/algorithm/generate

#include <algorithm>
#include <map>
#include <random>
#include <vector>
#include <cassert>

// note the use of srand and feed it with the return value of time()
void test_generate_random_values() {
    std::vector<int> v(10);
    srand(static_cast<unsigned int >(time(nullptr)));
    std::generate(v.begin(), v.end(),
        []() -> int {
        return static_cast<int>(random() % 0x3E7);
    });
}

void test_generator_with_state() {
    std::vector<int> v(10);
    struct Counter {
        int m_state = 0;
        int operator() () {
            return m_state++;
        }
    };
    std::generate(v.begin(), v.end(), Counter());
    assert(9 == v[9]);
}

int main() {
    test_generate_random_values();
    test_generator_with_state();
    return 0;
}