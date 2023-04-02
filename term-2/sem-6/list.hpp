#include <cstddef>
#include <memory>
#include <utility>
#include <type_traits>
// class List

template <typename T>
class List {
  struct Node;

 public:
  List() : begin_(nullptr), end_(new Node), length_(0) {
  }

  void PushBack(const T& value) {
    auto new_node = std::make_shared<Node>(Node{.value = value, .next = end_, .prev = {}});
    ++length_;
    if (begin_ == nullptr) {
      begin_ = new_node;
      end_->prev = begin_;
      begin_->next = end_;
    } else {
      auto prev = end_->prev.lock();
      prev->next = new_node;
      end_->prev = prev->next;
      prev->next->prev = prev;
    }
  }

  template <bool IsConst>
  class Iterator;

  using iterator = Iterator<false>;                                      // NOLINT
  using const_iterator = Iterator<true>;                                 // NOLINT
  using reverse_iterator = std::reverse_iterator<iterator>;              // NOLINT
  using reverse_const_iterator = std::reverse_iterator<const_iterator>;  // NOLINT
  using value_type = T;                                                  // NOLINT

  iterator begin() {  // NOLINT
    return iterator(begin_.get());
  }
  iterator begin() const {  // NOLINT
    return cbegin();
  }
  const_iterator cbegin() const {  // NOLINT
    return const_iterator(begin_.get());
  }

  iterator end() {  // NOLINT
    return iterator(end_.get());
  }
  iterator end() const {  // NOLINT
    return cend();
  }
  const_iterator cend() {  // NOLINT
    return const_iterator(end_.get());
  }

  reverse_iterator rbegin() {  // NOLINT
    return end();
  }

  template <bool IsConst>
  class Iterator {
   public:
    using difference_type = std::ptrdiff_t;                       // NOLINT
    using value_type = T;                                         // NOLINT
    using reference = std::conditional_t<IsConst, const T&, T&>;  // NOLINT

    Iterator() = default;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    Iterator& operator++() {
      ptr_ = ptr_->next.get();
      return *this;
    }

    Iterator operator++(int) const {
      auto tmp = *this;
      return ++tmp;
    }

    Iterator& operator--() {
      ptr_ = ptr_->prev.lock().get();
      return *this;
    }

    Iterator operator--(int) const {
      auto tmp = *this;
      return --tmp;
    }

    reference operator*() const {
      return ptr_->value;
    }

    T* operator->() const {
      return &(ptr_->value);
    }

    bool operator==(const Iterator& other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const Iterator& other) const {
      return !(*this == other);
    }

   private:
    friend List;

    explicit Iterator(Node* ptr) : ptr_(ptr) {
    }

   private:
    Node* ptr_ = nullptr;
  };

 private:
  struct Node {
    T value;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
  };

  std::shared_ptr<Node> begin_;
  std::shared_ptr<Node> end_;
  std::size_t length_;
};
