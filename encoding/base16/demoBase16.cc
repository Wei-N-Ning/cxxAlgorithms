
#include <cassert>
#include <iostream>

using namespace std;

short encode(unsigned char byte) {
    return (((byte / 16) + 'A') << 8) + (byte % 16) + 'A'; 
}

unsigned char decode(short two) {
    auto first = (two & 0b1111111100000000) >> 8;
    first = (first - 'A') * 16;
    auto second = (two & 0b11111111);
    second -= 'A';
    return first + second;
}

int main() {
    unsigned char byte = 0xA0;
    auto encoded = encode(byte);
    assert(byte == decode(encoded));
    return 0;
}
