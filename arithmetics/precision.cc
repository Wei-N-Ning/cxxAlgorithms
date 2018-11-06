#include <limits>
#include <cmath>
#include <cassert>

// source
// wkou, 

int main() {
    double r = std::numeric_limits<double>::min(); 
    assert(r > 0.0);
    return 0;
}
