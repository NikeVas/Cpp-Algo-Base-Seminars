#include <utility>
#include <iostream>
#include <algorithm>
#include <cassert>

//~ λ-expression
//* https://en.cppreference.com/w/cpp/language/lambda

//* Functional object
//| C-function
//| Class with overloaded operator()
//| (since C++11) λ-expression

//~ 0. auto

namespace auto_return {

auto Foo() {
  return 1;
}

auto Bar() {
  return true;
}

auto Boo(bool cond) -> bool {
  if (cond) {
    return false;
  }
  return 1;
}

//* Complicate return type

auto GetFoo() -> int* (*)(double) {
  return nullptr;
}

//* Return type depend on argument

//* Modern C++
auto Add(const auto& a, auto b) -> decltype(a + b) {
  // return a + b;
}

//* Old C++
template <typename T, typename U>
decltype(std::declval<T>() + std::declval<U>()) Add(T a, U b) {
}
}  // namespace auto_return

//~ 1. C-function && Callable class

namespace old_c_plus_plus {

bool FunComp(const int& lhs, const int& rhs) {
  return lhs < rhs;
}

void FunPrint(const int& x) {
  std::cout << x << " ";
}

void SomeFunction(int* array, size_t size) {
  struct Comp {
    bool operator()(const int& lhs, const int& rhs) {
      return lhs < rhs;
    }
  } comp;

  std::sort(array, array + size, FunComp);
  std::sort(array, array + size, Comp());
  std::sort(array, array + size, comp);

  struct Print {
    void operator()(const int& x) {
      std::cout << x << " ";
    }
  } printer;

  std::for_each(array, array + size, FunPrint);
  std::for_each(array, array + size, Print());
  std::for_each(array, array + size, printer);
}

//~ 2. λ-expression

namespace lambda {

template <typename T>
const T& AsConst(T& value) {
  return value;
}

void SomeFunction(int* array, size_t size) {
  //* [capture](args)spec{};
  //* [capture]{};

  std::sort(array, array + size,
            [](const int& lhs, const int& rhs) { return lhs < rhs; });

  std::for_each(array, array + size,
                [](const int& x) { std::cout << x << " "; });

  //? Return type

  [](bool cond) -> double {
    if (cond) {
      return 1.;
    }
    return 1;
  };

  [](bool cond) {
    if (cond) {
      return 1.;
    }
    return 1.;
  };

  //? Template lambda (since C++14) // (extent C++20)

  [](const auto& lhs, const auto& rhs) { return lhs < rhs; };

  //? Print with custom separator

  auto sep = " / ";

  [sep](const int& x) {  //! By copy
    std::cout << x << sep;
  };

  //? Sum array
  int sum = 0;

  std::for_each(array, array + size,
                [&sum](const int& x) {  //! By reference
                  sum += x;
                });

  //? Change variable captured by copy
  int x = 0;
  [x]() mutable {  //! Allow to change variable captured by copy
    x += 1;
    x += 15;
    return x;
  };
  assert(x == 0);

  //? Capture with name
  int x = 0;
  int z = 0;
  [y = x, &a = z]() { return y; };

  //? Capture by const ref
  int x = 0;
  [&x = std::as_const(x)]() {};

  //* To future
  int x = 0;
  [x = std::move(x)] mutable {};

  [=]() {};  //! (Bad style) Capture all by copy
  [&]() {};  //! (Bad style) Capture all by reference

  int x, y;
  [=, &x, &y]() {};
  [&, x, y]() {};

  //? λ-expression in class

  struct X {
    int x;

    void Foo() {
      [x = this->x] { std::cout << x << " "; };

      //! (Bad style)
      [this] {  //* Capture this "by reference"
        std::cout << x << " ";
      };

      //! (Bad style) (since C++17)
      [*this] {  //* Capture this "by copy"
        std::cout << x << " ";
      };

      [=] {};  //* Also capture this (as [=, this], "by reference")
      [&] {};  //* Also capture this (as [&, this], "by reference")
    }
  };

  bool (*comp)(const int*, const int*) = [](const int* lhs, const int* rhs) {
    return *lhs < *rhs;
  };

  auto lambda = [x](int x) -> bool {};

  struct __SOME_NAME__ {
    bool operator()(int x) {
    }

    int x;
  };
}
}  // namespace lambda

}  // namespace old_c_plus_plus
