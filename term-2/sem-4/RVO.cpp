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

// Object RVO() {
//   return Object{};
// }

Object NRVO() {
  Object object;
  return object;
}

int main() {
  auto object = NRVO();
}
