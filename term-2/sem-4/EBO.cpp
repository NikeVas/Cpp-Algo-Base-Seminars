#include <iostream>

struct Base {
};

struct Derived : Base {
  int b;
};

int main() {
  std::cout << "Base " << sizeof(Base) << "\n";
  std::cout << "Derived " << sizeof(Derived) << "\n";
}
