#include <limits>
#include <cmath>
#include <cassert>

// source
// wkou, 

int main() {
    assert(! std::isnan(static_cast<double>(0xE0000000)));
    
    return 0;
}
