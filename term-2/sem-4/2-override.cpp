#include <iostream>

struct Base {
  virtual void Foo() const {
    std::cout << "Base::Foo();\n";
  }
};

struct Derived : Base {
  void Foo() const override {
    std::cout << "Derived::Foo();\n";
  }
};

struct SuperDerived : Derived {
  void Foo() const override {
    std::cout << "SuperDerived::Foo();\n";
  }
};

int main() {
  SuperDerived super_derived;
  Derived& derived = super_derived;
  Base& base = derived;

  base.Foo();
  derived.Foo();
  super_derived.Foo();
}
