#include <iostream>
#include <random>

struct Base {
  virtual void Foo() {
    std::cout << "Base::Foo();\n";
  }
  void Bar() {
    std::cout << "Base::Bar();\n";
  }
};

struct Derived : Base {
  void Foo() {
    std::cout << "Derived::Foo();\n";
  }
  virtual void Bar() {
    std::cout << "Derived::Bar();\n";
  }
};

struct ADerived : Base {
  void Foo() {
    std::cout << "ADerived::Foo();\n";
  }
};

struct BDerived : Base {
  void Foo() {
    std::cout << "BDerived::Foo();\n";
  }
};

struct SuperDerived : Derived {
  void Foo() {
    std::cout << "SuperDerived::Foo();\n";
  }
  void Bar() {
    std::cout << "SuperDerived::Bar();\n";
  }
};

int main() {
  Derived derived;
  Base& base = derived;
  base.Foo();

  std::cout << "=================\n";
  Base* base_ptr = nullptr;

  srand(time(NULL));
  if (rand() % 2 == 0) {  // Runtime solution (vtable)
    base_ptr = new ADerived;
  } else {
    base_ptr = new BDerived;
  }
  base_ptr->Foo();

  std::cout << "=================\n";
  SuperDerived super_derived;
  Derived& derived_ref = super_derived;
  Base& base_ref = super_derived;

  base_ref.Bar();
  derived_ref.Bar();
  super_derived.Bar();
}
