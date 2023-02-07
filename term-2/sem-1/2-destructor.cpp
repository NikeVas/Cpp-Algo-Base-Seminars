#include <iostream>

class Object {
 public:
  explicit Object(const char* name) : name_(name) {
  }

  ~Object() {
    std::cout << "Call Object::" << name_ << " destructor\n";
  }

 private:
  const char* name_;
};

int main() {
  Object{"temp"};

  auto long_term = Object{"long_term"};

  {
    auto short_term = Object{"short_term"};
  }

//   long_term.~Object();
}
