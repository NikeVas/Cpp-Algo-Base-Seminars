#include <iostream>

class Object {
public:
  Object() { std::cout << "Object::Object()\n"; }
  Object(const Object&) { std::cout << "Object::Object(const Object&)\n"; }
  Object& operator=(const Object&) { std::cout << "Object& Object::operator=(const Object&)\n"; return *this; }
  Object(Object&&) { std::cout << "Object::Object(Object&&)\n"; }
  Object& operator=(Object&&) { std::cout << "Object& Object::operator=(Object&&)\n"; return *this; }
  ~Object() { std::cout << "Object::~Object()\n"; }
};

struct B {
  B() { std::cout << "B::B()\n"; }
  ~B() { std::cout << "B::~B()\n"; }
};

struct A : Object {
  A() { std::cout << "A::A()\n"; }
  ~A() { std::cout << "A::~A()\n"; }

public:
  B b;
};

int main() {
  A a;
}
