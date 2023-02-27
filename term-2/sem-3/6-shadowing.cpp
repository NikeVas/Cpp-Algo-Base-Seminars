#include <iostream>

struct Base {
  void F() { std::cout << "Base::F();\n"; }
};

struct Derived : Base {
  using Base::F;
  void F() { std::cout << "Derived::F();\n"; }
};

struct A {
  int x;
  int y;

  A(int, int) {}
};

struct B : A {
  using A::A;
  void Foo() {}

  int a = 0;
};

int main() {
  Derived d;
  d.F();
  d.Base::F();
//   d.Base::F(0);
//   d.F(0);

  B b(0, 0);

  Base& base = d;
  base.F();
}
