#include <iostream>

//~ Operator overloading
//* https://en.cppreference.com/w/cpp/language/operators

//* Can be overloaded
//|   + - * / %   //   + - 
//|   ^ & | ~  //   << >>
//|   =
//|   < > == != <= >=   //    <=> (since C++20)
//|   += -= *= /= %= 
//|   ^= &= |= >>= <<=   
//|   ! && || 
//|   ++ --   //   ++ --
//|   , ->* 
//|   ->
//|   ( ) 
//|   [ ]    //   (more than one subscripts, since C++23)

//! operator -> must either return 
//| a raw pointer
//| an object (by reference or by value) for which operator -> is in turn overloaded

//! lose short-circuit evaluation
//|   && ||

//! (until C++17) lose their special sequencing properties
//|   && || ,
//  No: function call

//* Cannot be overloaded
//|   :: . .* ?:
//* New operator cannot be created

//* Not possible to change the 
//| precedence
//| grouping
//| number of operands of operators

//~ 0. Friend declaration
//~ 0.1 Friend functions declarations

namespace friend_functions_declarations {

class X {
  int data_;

  friend void Foo(X);
};

void Foo(X x) {
  x.data_;
}

}  // namespace friend_functions_declarations

//~ 0.2 Friend functions definition 
//* Allowed in non-local class definitions

namespace friend_functions_definition {

class X {
  int data_;

  friend void Foo(X x) {
    x.data_;
  }
};

}  // namespace friend_functions_definition


//~ 0.3 Friend class declaration

namespace friend_class_declarations {

class X {
  int data_;

  friend class Y; 
};

class Y {
  void Foo(X x) {
    x.data_;
  }
};

}  // namespace friend_class_declarations

//~ 1. Unary operator
//~ 1.1 Unary prefix operator
//? + - ++ -- ! ~

//* Expresion  |  As member function  |  As non-member function
//*     @a     |  (a).operator@ ( )   |  operator@ (a)


namespace unary_operator {

struct Complex {
  double x;
  double y;  

  Complex operator+() const {
    return *this;
  }
};

Complex operator-(const Complex& object) {
  return {-object.x, -object.y};
}

}  // namespace unary_operator

//~ 1.2 Unary postfix operator
//? ++ --

//` ¯\_(ツ)_/¯
//* Expresion  |  As member function  |  As non-member function
//*     a@     |  (a).operator@ (0)   |  operator@ (a, 0)

//~ 1.3 Increment and decrement

namespace inc_and_dec {

struct X {

  X& operator++() {
    return *this;
  }
  
  X operator++(int) {
    X old = *this;
    operator++();
    return old;
  }
};

X& operator--(X& object) {
  return object;
}

X operator--(X& object, int) {
  X old = object;
  --object;
  return old;
}

}  // namespace inc_and_dec

//~ 2. Member of pointer	(->)

//* Expresion   |  As member function   |  As non-member function
//*     a->     |  (a).operator-> ()    |  cannot be non-member

//! operator -> must either return 
//| a raw pointer
//| an object (by reference or by value) for which operator -> is in turn overloaded

namespace member_of_pointer {
  
struct A {
  void Foo() {
    std::cout << "A::Foo\n";
  } 
};

struct B {
  A* ptr = new A;

  A* operator->() {
    return ptr;
  }
};

struct Wrapper {
  B* ptr = new B;

  B& operator->() {
    return *ptr;
  }
};

//* Code
//| Wrapper w;
//| w->Foo();
//* Output
//| A::Foo
};

//~ 3. Binary operator

//* Expresion   |  As member function   |  As non-member function
//*     a@b     |  	(a).operator@ (b)   |  operator@ (a, b)
//~ 3.1 Binary arithmetic operators
//|   += -= *= /= %=
//|   + - * / %
//?  += <-> +

namespace binary_arithmetic_operators {

struct Complex {

  double x;
  double y;

  Complex(int x) : x(x), y(0) {}  // NOLINT

  Complex& operator+= (const Complex& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Complex operator+ (const Complex& other) const {
    Complex tmp = *this;
    tmp += other;
    return tmp;
  }
};

//? Complex c; int i;
//? c + i => (c).operator+(i) // OK
//? i + c => (i).operator+(c) // CE

Complex& operator-= (Complex& lhs, const Complex& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

Complex operator- (const Complex& lhs, const Complex& rhs) {
  Complex tmp = lhs;
  tmp -= rhs;
  return tmp;
}

//? c - i  => operator-(c, i) // OK
//? i - c  => operator-(i, c) // OK

}  // namespace binary_arithmetic_operators

//~ 3.2 Comparison operators
//|   < > == != <= >=   //    <=> (since C++20)
//* std expect only < 

namespace comparison_operator {

struct Point {
  double x;
  double y;
};

bool operator<(const Point& lhs, const Point& rhs) {
  return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x; 
}
bool operator>(const Point& lhs, const Point& rhs) {
  return rhs < lhs;
}
bool operator<=(const Point& lhs, const Point& rhs) {
  return !(rhs < lhs);
}
bool operator>=(const Point& lhs, const Point& rhs) {
  return !(lhs < rhs);
}
bool operator==(const Point& lhs, const Point& rhs) {
  return !(lhs < rhs || rhs < lhs);
}
bool operator!=(const Point& lhs, const Point& rhs) {
  return !(lhs == rhs);
}

}  // namespace comparison_operator

//~ 3.3 Stream extraction and insertion

namespace stream {
class Point {
  double x;
  double y;

  friend std::ostream& operator<<(std::ostream&, const Point&);
  friend std::istream& operator>>(std::istream&, Point&);
};

std::ostream& operator<<(std::ostream& os, const Point& obj) {
  os << "(" << obj.x << ", " << obj.y << ")";
  return os;
}

std::istream& operator>>(std::istream& is, Point& obj) {
  char c;
  // (x, y)
  is >> c >> obj.x >> c >> obj.y >> c;
  return is;
}

//* Point p;
//* std::cout << p;

}  // namespace stream

//~ 3.4 Bitwise arithmetic operators
//* See: C++ named requirements: BitmaskType
//| https://en.cppreference.com/w/cpp/named_req/BitmaskType


//~ 4. Assignment

//* Expresion   |  As member function   |  As non-member function
//*     a=b     |  	(a).operator= (b)   |  cannot be non-member

//* Default generated by compiler 
//* Next term
// 4.1 Copy assignment
// 4.2 Move assignment 

//~ 5. Function call

//* Expresion   |  As member function     |  As non-member function
//*  a(b...)    |  (a).operator()(b...)   |  cannot be non-member

namespace function_call {

struct Linear {
    double a, b;
 
    double operator()(double x) const {
      return a * x + b;
    }

    void operator()() const {}
};

//* Linear l;
//* l(5);
//* l();

}  // namespace function_call

//~ 6. Array subscript operator

//* Expresion   |  As member function     |  As non-member function
//*  a[b]       |  (a).operator()[b]      |  cannot be non-member
//| since C++23
//|  a[b...]    |  (a).operator()[b...]   |  cannot be non-member 

namespace array {

template<typename T, std::size_t N>
struct Array{
  T data[N];

  T& operator[](size_t i) {
    return data[i];
  }

  const T& operator[](size_t i) const {
    return data[i];
  }
};

}  // namespace array

//~ 7. Rarely overloaded operators
//* address-of operator   
//| &
//? std::addressof

//* boolean logic operators   
//| && ||
//* comma operator    
//| ,

//* member access through pointer to member    
//| ->*

//~ 8. User-defined conversion function (operator /* type */)
//* <-> Conversion constructor

namespace user_defined_conversion_function {

struct Rational {
  // Rational(BigInteger);
};

struct BigInteger {

  explicit operator Rational() const {
    
  }

  explicit operator int() const {

  }

};

//| void foo(int);
//| BigInteger big_int;
//! foo(big_int);  // CE
//| foo(static_cast<int>(big_int));  // OK

}  // namespace user_defined_conversion_function

//~ 8.1 (since C++11) Contextual conversions (operator bool) 

//| the controlling expression of if, while, for;
//| the operands of the built-in logical operators !, && and ||;
//| the first operand of the conditional operator ?:;
//| the predicate in a static_assert declaration;
// the expression in a noexcept specifier;
// (since C++20) the expression in an explicit specifier;

namespace operator_bool_overloading {

struct Bit {

  explicit operator bool() {

  }

};

//* Code
//| Bit b;
//| if (b) {} // OK
//| bool b1 = b; // CE
//* Bit Foo();
//* bool b1 = Foo();
//| bool b2 = static_cast<bool>(b); // OK

}

//~ 9. User-defined literals
//* https://en.cppreference.com/w/cpp/language/user_literal

namespace user_defined_literals {

//| auto a = 3f;
//| auto b = 3z; // size_t
//| auto str = "string"s // std::string

struct BigInteger {};
  
BigInteger operator""_bi(const char* str, std::size_t size);
BigInteger operator""_bi(unsigned long long int value);  // NOLINT

//| "1245434567898890098765434567876556543234567890098765434567654"_bi
//| BigInteger("1245434567898890098765434567876556543234567890098765434567654");

}  // namespace user_defined_literals
