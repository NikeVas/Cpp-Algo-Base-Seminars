#include <bits/iterator_concepts.h>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <list>
#include <iostream>

// before C++11

namespace CPP03 {

template <typename T, T N>
struct IntegralConst {
  static const T Value = N;
};

template <int64_t N>
struct Fib {
  static const int64_t Value = Fib<N-1>::Value + Fib<N-2>::Value;
};

template <>
struct Fib<0> {
  static const int64_t Value = 0;
};

template <>
struct Fib<1> {
  static const int64_t Value = 1;
};

namespace detail {

template <int64_t N, int64_t Current = N - 1>
struct IsPrimeImpl {
  static const bool Value = (N % Current != 0) && IsPrimeImpl<N, Current - 1>::Value;
};

template <int64_t N>
struct IsPrimeImpl<N, 2> {
  static const bool Value = (N % 2 != 0);
};

}  // namespace detail


template <int64_t N>
requires (N > 1)
struct IsPrime {
  static const bool Value = detail::IsPrimeImpl<N>::Value;
};

template <>
struct IsPrime<2> : IntegralConst<bool, true> {};


//  Прогаем ребята!!!

template <int64_t Base>
struct Square {
  static const int64_t Value = Base * Base;
};



template <int64_t Base, int64_t Exp>
struct Pow {
  static const int64_t Value = Exp % 2 == 0
                             ? Square<Pow<Base, Exp / 2>::Value>::Value
                             : Pow<Base, Exp - 1>::Value * Base;
};

template <int64_t Base>
struct Pow<Base, 0> {
  static const int64_t Value = 1;
};

}  // namespace CPP03

// C++11

namespace CPP11 {

constexpr int64_t Square(int64_t base) {
  return base * base;
}

constexpr int64_t Pow(int64_t base, int64_t exp) {
  return exp == 0 ? 1 : ( exp % 2 == 0 ? Square(Pow(base, exp / 2)) : Pow(base, exp - 1) * base);
}

}  // namespace CPP11

// C++14

namespace CPP14 {
constexpr int64_t Square(int64_t base) {
  return base * base;
}

constexpr int64_t Pow(int64_t base, int64_t exp) {
  int64_t pow;
  if (exp == 0) {
    pow = 1;
  } else if (exp % 2 == 0) {
    pow = Square(Pow(base, exp / 2));
  } else {
    pow = Pow(base, exp - 1) * base;
  }
  return pow;
}
}  // namespace CPP14

namespace CPP17 {

template <typename Iterator>
std::ptrdiff_t Distance(Iterator begin, Iterator end) {
  if constexpr (std::random_access_iterator<Iterator>) {
    return end - begin;
  } else {
    std::ptrdiff_t dist = 0;
    for (; begin != end; ++begin, ++dist) {}
    return dist;
  }
}

}  // namespace CPP17

namespace detail {

template <bool IsRandomAccess>
struct DistanceImpl/*<true>*/ {
  template <typename Iterator>
  inline static std::ptrdiff_t Distance(Iterator begin, Iterator end) {
    return end - begin;
  }
};

template <>
struct DistanceImpl<false> {
  template <typename Iterator>
  inline static std::ptrdiff_t Distance(Iterator begin, Iterator end) {
    std::ptrdiff_t dist = 0;
    for (; begin != end; ++begin, ++dist) {}
    return dist;
  }
};

}  // namespace detail

template <typename Iterator>
std::ptrdiff_t Distance(Iterator begin, Iterator end) {
  return detail::DistanceImpl<std::random_access_iterator<Iterator>>::Distance(begin, end);
}

constexpr int Foo(int x) {
  if constexpr(std::is_constant_evaluated()) {
    return 1;
  } else {
    return 2;
  }
}

int main() {
  std::list l{1, 2, 3, 4, 5};
  int x;
  std::cin >> x;
  std::cout << Foo(x);
}
