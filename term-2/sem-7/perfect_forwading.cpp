#include <type_traits>
#include <utility>
#include <memory>
#include <vector>
#include <iostream>
#include <concepts>

struct NoDefaultConstructible {
  NoDefaultConstructible(std::unique_ptr<int>) {}; // NOLINT
  NoDefaultConstructible(int, int) {};

  NoDefaultConstructible(const NoDefaultConstructible&) = delete;
  NoDefaultConstructible(NoDefaultConstructible&&) = delete;
};

template <typename T>
T&& Forward(std::remove_reference_t<T>& value) {
    return static_cast<T&&>(value);
}

template <typename T>
T&& Forward(std::remove_reference_t<T>&& value) {
    return static_cast<T&&>(value);
}



template <class T>
struct List {
  struct Node {
    T value;
  };

  template<typename... Arg>
  void EmplaceBack(Arg&&... args) {
    // T{args...} //-> T{arg0, arg1, ...}
    // T{func(args)...} //-> T{func(arg1), func(arg2), ...}
    // T{args * args...}
    head = new Node{T{std::forward<Arg>(args)...}};
  }

  void PushBack(const T& object) {
    head = new Node(object);
  }

  void PushBack(T&& object) {
    head = new Node(std::move(object));
  }

  Node* head;
};

template<typename Head>
auto Sum(const Head& head) {
  return head;
}

template<typename Head, typename... Args>
auto Sum(const Head& head, const Args&... args) {
  return head + Sum(args...);
}

template<typename... Args>
auto FoldSum(const Args&... args) {
  return (args + ...);
}

template<char Sep, char End, typename Head, typename... Args>
void Println(const Head& head, const Args&... args) {
  std::cout << head;
  ((std::cout << Sep << args), ...);
  std::cout << End;
}

template<typename T, typename U>
struct IsSame {
    static const bool value = false;
};

template<typename T>
struct IsSame<T, T> {
    static const bool value = true;
}

template<bool Cond, typename T = void>
struct EnableIf {};

template<typename T>
struct EnableIf<true, T> { using type = T; };

template<bool Cond, typename T = void>
using EnableIfT = EnableIf<Cond, T>::type;

template<std::same_as<int>... Args>
auto FoldIntSum(const Args&... args) {
  return (args + ...);
}

template<typename... Args, std::enable_if_t<(std::is_same_v<Args, int> && ...)>>
auto FoldIntSum17(const Args&... args) {
  return (args + ...);
}


int main() {
  List<NoDefaultConstructible> list;

  auto&& x = std::make_unique<int>(0);

//   list.EmplaceBack(std::make_unique<int>(0));
  list.EmplaceBack(0, 0);

  Println<'%', '='>(0, 1, 2, 3, 4, 5);
}

