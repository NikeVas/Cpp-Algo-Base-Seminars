struct A {
  A(int, int) {}
};

struct B : A {
  B() : A(0, 0) {}

  B(int, int) : B() {}
};


int main() {
  B b(0, 0);
}
