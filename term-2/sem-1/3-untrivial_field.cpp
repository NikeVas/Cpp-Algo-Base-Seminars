#include <iostream>

struct Object {
  ~Object() {
    std::cout << "Object::~Object\n";
  }
};

struct ObjectCollection {
  ~ObjectCollection() {
    std::cout << "ObjectCollection::~ObjectCollection\n";
  } //? Before or arter object destructor

  Object a, b;
};

int main() {
  [[maybe_unused]] auto _ = ObjectCollection{};
}
