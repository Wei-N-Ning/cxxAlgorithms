
#include <cstdint>
#include <cassert>

// NOTE
// had this question at work: can a uintptr_t (__UINTPTR_TYPE__) be 
// statically-cast to an uint type

// source:
// stackoverflow: converting a pointer into an integer


void test_cast_uintptr_to_const_void_ptr() {
    // this won't compile  -- use reinterpret_cast<>
    //using const_pointer_p = const void *;
    using const_pointer_p = uint64_t;
    uintptr_t value = 0xDEAD;
    const_pointer_p pointer = static_cast<const_pointer_p>(value);
    assert(pointer);
}

void test_cast_const_void_ptr_to_uint() {
    uintptr_t pointer = 0xDEAD;
    uint64_t value = static_cast<uint64_t>(pointer);
    assert(0xDEAD == value);
    
    // won't compile
    // use reinterpret_cast<>
    //uint64_t val = 0xBEEF;
    //uint64_t ptr_casted = static_cast<uint64_t>(&val);
    //assert(0xBEEF == ptr_casted);
}

int main() {
    test_cast_uintptr_to_const_void_ptr();
    test_cast_const_void_ptr_to_uint();
    return 0;
}
