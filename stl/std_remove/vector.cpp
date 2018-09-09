#include <algorithm>
#include <vector>
#include <iostream>
// source
// more exceptional C++ item 2 P7
// std::remove() does not physically remove the element from a 
// container
// it shuffles up the un-removed objects to fill in the gaps left by 
// the removed objects
// leaving at the end one "dead" object for each remove object 
// finally remove() returns an iterator pointing to the first dead 
// object or the end iterator if no one removed

template<typename T>
inline void printVec(std::vector<T>& v) {
    if (! v.empty()) {
        for (const auto& e : v) {
            std::cout << e << ", ";
        }
        std::cout << std::endl; 
    }
}

void test_removeFromVector() {
    std::vector<int> v{1, 2, 3, 1, 2, 3, 1, 2, 3};
    std::remove(v.begin(), v.end(), 3);
    // the object at the end may have their original values or they
    // may not - they were copied to fill in the gaps but DO NOT 
    // rely on that
    // i.e. this is different from swap-remove !!!
    printVec(v);
}

// source more exception item 2 P8
// recall //// remove() returns an iterator pointing to the first 
// dead elements. ////
void test_removeThenErase() {
    std::vector<int> v{1, 2, 3, 1, 2, 3, 1, 2, 3};
    v.erase(std::remove(v.begin(), v.end(), 3), v.end());
    printVec(v);
}

// source more exception item 2 P10
// use advance() and copy()
void test_removeByCopy() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
    // to remove element at index-4
    auto iter = v.begin();
    std::advance(iter, 4);
    auto from = iter;
    std::copy(++from, v.end(), iter);
    v.pop_back();
    printVec(v);
}

int main() {
    test_removeFromVector();
    test_removeThenErase();
    test_removeByCopy();
    return 0;
}
