#include <iostream>

struct Base {
  Base() {
    Foo();
  }

  virtual void Foo() = 0;
};

void Base::Foo() {
  std::cout << "Base\n";
}

struct Derived : Base {
  Derived() {
    Foo();
  }

  void Foo() override {
    std::cout << "Derived\n";
  }
};

int main() {
  Derived derived;
  // Base b; //! CE
}
