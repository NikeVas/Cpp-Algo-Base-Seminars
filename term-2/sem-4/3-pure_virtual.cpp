#include <iostream>

struct IPrinter {
  virtual void Print() = 0;
};

struct StdoutPrinter : IPrinter {
  void Print() override {
    std::cout << "Stdout";
  }
};

struct StderrPrinter : IPrinter {
  void Print() override {
    std::cerr << "Stderr";
  }
};

int main() {
  IPrinter* p = new StdoutPrinter;
}
