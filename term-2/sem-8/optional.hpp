#pragma once

#include <cstddef>
#include <new>
#include <utility>

struct NulloptT {
  explicit NulloptT(int) {
  }
};

inline NulloptT nullopt = NulloptT(0);

struct InPlaceT {
  explicit InPlaceT() = default;
};

inline InPlaceT in_place{};

template <typename T>
class Optional {
 public:
  Optional() = default;
  Optional(NulloptT){};  // NOLINT

  template <class U>
  Optional(U&& value) : empty_(false) {  // NOLINT
    new (data_) T(std::forward<T>(value));
  }

  template <class... Args>
  explicit Optional(InPlaceT, Args&&... args) : empty_(false) {
    new (data_) T(std::forward<Args>(args)...);
  }

  Optional(const Optional& other) : empty_(other.empty_) {
    if (other.empty_) {
      return *this;
    }
    new (data_) T(std::launder(*reinterpret_cast<T*>(other.data_))); 
  }

 private:
  void Clear() {
    if (!empty_) {
      reinterpret_cast<T*>(data_)->~T();
      empty_ = true;
    }
  }

 private:
  alignas(T) std::byte data_[sizeof(T)];
  bool empty_ = true;
};
