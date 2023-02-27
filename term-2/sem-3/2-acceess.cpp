class Base {
 private:
  void F() {
  }

 public:
  void G() {
  }

 protected:
  void H() {
  }
};

class Derived : public Base {
  void Foo() {
    G();
    H();
    F();  // CE
  }
};

class ProtectedDerived : protected Base {
  void Foo() {
    G();
    H();
    F();  // CE
  }
};

class ProtectedDerivedDerived : public ProtectedDerived {
  void Foo() {
    G();
    H();
    F();  // CE
  }
};

class PrivateDerived : private Base {
  void Foo() {
    G();
    H();
    F();  // CE
  }
};

class PrivateDerivedDerived : public PrivateDerived {
  void Foo() {
    G();  // CE
    H();  // CE
    F();  // CE
  }
};

int main() {
  Derived d;

  d.G();
  d.H();  // CE
  d.F();  // CE

  ProtectedDerived pd;

  pd.G();  // CE

  PrivateDerived prd;

  prd.G(); // CE

}
