#include <iostream>

struct Derived;

struct Base {
  void F() {
  }
  Base() = default;
  Base(const Derived&) = delete; // {  std::cout << "Construct";  }
};

struct Derived : Base {
  void G() {
  }
};

int main() {
  Derived d;
//   Base b = d;
  Base& rb = d;
  Base* pb = &d;
  rb.F();
  rb.G(); // CE
//   b.F();
//   b.G();
}
