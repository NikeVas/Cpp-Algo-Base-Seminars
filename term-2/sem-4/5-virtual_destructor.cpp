#include <iostream>

struct Base {
  virtual void Foo() = 0;
  virtual ~Base() = default;
};

struct Derived : Base {

  Derived() : ptr_(new int) {
  }

  void Foo() override {
  }

  ~Derived() override {
    delete ptr_;
  }

 private:
  int* ptr_;
};

int main() {
  Base* ptr = new Derived();
  delete ptr;
}
