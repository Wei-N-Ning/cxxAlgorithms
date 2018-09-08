// source
// more exception item 9 P57
// An in depth look at postincrement operator and the potential side 
// effect/

// _[0x100000f56] <+22>: mov    ecx, eax
// _[0x100000f58] <+24>: add    ecx, 0x1
// _[0x100000f5b] <+27>: mov    dword ptr [rbp - 0xc], ecx
// _[0x100000f5e] <+30>: mov    esi, eax
// _[0x100000f60] <+32>: call   0x100000f70               ; dasm_this()::$_0::operator()(int) const at postincrement.cpp:7
// _[0x100000f65] <+37>: mov    dword ptr [rbp - 0x10], eax
// _[0x100000f68] <+40>: add    rsp, 0x10
// _[0x100000f6c] <+44>: pop    rbp
// _[0x100000f6d] <+45>: ret    
// (lldb) dis -F intel -a 0x100000f70
// _`dasm_this()::$_0::operator()(int) const:
// _[0x100000f70] <+0>:  push   rbp
// _[0x100000f71] <+1>:  mov    rbp, rsp
// _[0x100000f74] <+4>:  mov    qword ptr [rbp - 0x8], rdi
// _[0x100000f78] <+8>:  mov    dword ptr [rbp - 0xc], esi
// _[0x100000f7b] <+11>: mov    esi, dword ptr [rbp - 0xc]
// _[0x100000f7e] <+14>: add    esi, 0x3e8
// _[0x100000f84] <+20>: mov    dword ptr [rbp - 0x10], esi
// _[0x100000f87] <+23>: mov    eax, dword ptr [rbp - 0x10]
// _[0x100000f8a] <+26>: pop    rbp
// _[0x100000f8b] <+27>: ret

// note how ecx holds the incremented value whereas eax still holds 
// the old value, which is used by the lambda callee
void dasm_this() {
    auto func = [](int arg) -> int {
        int temp = arg + 1000;
        return temp;
    };
    
    int a = 1;
    func(a++);
}

// P58
// f(a++);
// 
// if f is a macro, 
// #define f(x) x
// #define f(x) (x, x, x)
// #define f(x)
// "a++" could be evaluated many times or not at all
//

// if f is a function then "a++" is evaluated and result passed to 
// f() - the previous value is passed to f as a temp object; the arg 
// can not be a non-const reference
// similar situation if f is a function object 
// 
// if a is a macro
// definition specific
//
// if a is an object,
// it must be a type which define operator++(int) operator
// the postincrement operator should return the previous value of a
////// always preserve natural semantics for overloaded operators
// "DO as INTs DO" ////////
struct Incr {
    int m_value = 0;
    Incr operator++(int);
};

Incr Incr::operator++(int) {
    Incr old;
    old.m_value = m_value;
    m_value += 1;
    return old;
}

void incr_this() {
    auto func = [](Incr arg) -> int {
        int temp = arg.m_value;
        return temp + 1000;
    };

    Incr a;
    func(a++);
}

// P60
// if f() emits an exception.
// f(a++);
// ensures that a++ and all its side effects have been completely 
// successful
// f(a); a++;
// ensures that a++ has not been performed

// P61
// if a is an iterator and f is erase(), f(a); a++; operates on an 
// invalid iterator;
// f(a++) is safe

int main() {
    dasm_this();
    incr_this();
    return 0;
}
