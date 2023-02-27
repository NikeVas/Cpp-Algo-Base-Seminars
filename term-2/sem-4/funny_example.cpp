struct Base {};

struct Derived : private Base {};

struct SuperDerived : public Derived {
  void Foo() {
    ::Base b;
  }
};

int main() {
}
