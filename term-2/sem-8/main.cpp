#include <cstdlib>
#include <iostream>
#include <new>

void* operator new(size_t count) {
    std::cout << "Call new\n";
    auto* p = std::malloc(count);
    if (p == nullptr) {
        throw std::bad_alloc();
    }
    return p;
}

// void operator delete(void* ptr) {
//     std::free(ptr);
// }

struct Tag {};

void* operator new(size_t count, std::nothrow_t) noexcept {
    std::cout << "Placment new\n";
    return nullptr;
}

int main() {
    using T = int;
    auto* p = new T(3);
    auto* pp = (int*)std::malloc(sizeof(T));
    new (pp) T(5);
    auto* ppp = operator new(sizeof(T));
    std::cout << *p << " " << *static_cast<int*>(pp) << "\n";
    new (std::align_val_t(16)) T(5);
    delete p;
    pp->~T();
    std::free(pp);
    operator delete(ppp);

}
