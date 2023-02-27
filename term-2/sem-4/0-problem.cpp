#include <iostream>

struct Base {
  void Foo() {
    std::cout << "Base::Foo();\n";
  }
};

struct Derived : Base {
  void Foo() {
    std::cout << "Derived::Foo();\n";
  }
};

int main() {
  Derived derived;
  Base& base = derived;
  base.Foo();
}
