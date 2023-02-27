#include <iostream>

struct Base {
  virtual ~Base() = default;
};

struct Derived : Base {
  void Print() {
    std::cout << "Derived " << a << "\n";
  }

  int a = 10;
};

int main() {
  Derived derived;
  Base base;

  Base& downcast1 = derived;
  Base& downcast2 = static_cast<Base&>(derived);
  Base& downcast3 = dynamic_cast<Base&>(derived);


  // Derived& upcast1 = base; //! CE
  // Derived& upcast2 = static_cast<Derived&>(base); // unsafe
  // upcast2.Print(); // UB

//   Derived& upcast3 = dynamic_cast<Derived&>(base); // throw std::bad_cast
//   Derived* upcast4 = dynamic_cast<Derived*>(&base); // return nullptr

  Base& derived_under_base = derived;
  if (auto* object = dynamic_cast<Derived*>(&derived_under_base); object != nullptr) {
    object->Print();
  }

}
