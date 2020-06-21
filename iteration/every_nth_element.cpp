
#include <vector>
// I have only one working impl which is:
int main() {
    std::vector<int> v{0, 0};

    // every 2-nd element
    for (auto it{std::cbegin(v), end{std::cend(v}; it < end; it += 2) {
        // do stuffs but do not modify it;
        // I can create temporary "offset" iter from it such as:
        *(std::next(it, 1));
    }

}
