#include <cstddef>
#include <utility>

template <class T>
class Vector {
 public:
  Vector() : array_(new T[1]), capacity_(1), size_(0) {
  }
  Vector(const Vector& other)
    : array_(new T[other.capacity_])
    , capacity_(other.capacity_)
    , size_(other.size_)
  {
    for (std::size_t i = 0; i < size_; ++i) {
        array_[i] = other.array_[i];
    }
  }

  Vector& operator=(const Vector& other) {
    if (this == &other) {
      return *this;
    }
    auto tmp = other;
    Swap(tmp);
    return *this;
  }

  void Swap(Vector& other) {
    std::swap(array_, other.array_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

// РАБОТАЕМ РЕБЯТАААА!!!!!!!! ЗА СЕБЯ И ЗА САШКУ!
  ~Vector() {
    delete[] array_;
  }

  const T& operator[](std::size_t idx) const {
    return array_[idx];
  }

  T& operator[](std::size_t idx) {
    return array_[idx];
  }

  void PushBack(const T& x) {
    if (size_ == capacity_) {
      Reallocation();
    }
    array_[size_] = x;
    ++size_;
  }

  size_t Size() const {
    return size_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  void PopBack() {
    --size_;
  }

  const T& Front() const {
    return array_[0];
  }

  const T& Back() const {
    return array_[size_ - 1];
  }

  T& Front()  {
    return array_[0];
  }

  T& Back()  {
    return array_[size_ - 1];
  }

 private:
  void Reallocation() {
    capacity_ *= kMultiplyFactor;
    auto tmp = new T[capacity_];
    for (std::size_t i = 0; i < size_; ++i) {
      tmp[i] = array_[i];
    }
    delete[] array_;
    array_ = tmp;
  }

 private:
  T* array_;
  std::size_t capacity_;
  std::size_t size_;
  inline static const std::size_t kMultiplyFactor = 2;
};
