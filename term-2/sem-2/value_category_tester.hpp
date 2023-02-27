#pragma once

#include <iostream>
#include <iomanip>

template<typename T>
struct ValueCategory {
    // Or can be an integral or enum value
    static constexpr auto value = "prvalue";
};

template<typename T>
struct ValueCategory<T&> {
    static constexpr auto value = "lvalue";
};

template<typename T>
struct ValueCategory<T&&> {
    static constexpr auto value = "xvalue";
};

// Double parens for ensuring we inspect an expression,
// not an entity
#define VALUE_CATEGORY(expr) ValueCategory<decltype((expr))>::value

#define PRINT_VALUE_CATEGORY(expr) \
do { \
  std::cout << std::setw(12)  << #expr << "\t" << VALUE_CATEGORY(expr) << "\n"; \
} while(0)

///////////////////нематериальны////////////////////////////////////////////////////////////

template<typename T>
struct MarcdownValueCategory {
    // Or can be an integral or enum value
    static constexpr auto value = "prvalue";
};

template<typename T>
struct MarcdownValueCategory<T&> {
    static constexpr auto value = "&ensp; lvalue";
};

template<typename T>
struct MarcdownValueCategory<T&&> {
    static constexpr auto value = "&ensp; xvalue";
};

#define VALUE_CATEGORY(expr) ValueCategory<decltype((expr))>::value


#define MARCDOWN_VALUE_CATEGORY(expr) \
do { \
  std::cout << "|`" << std::setw(12) << #expr << "` | >! " << std::setw(15) << MarcdownValueCategory<decltype((expr))>::value << " !< | \n"; \
} while(0)
