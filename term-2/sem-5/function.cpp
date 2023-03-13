#include <functional>
#include <memory>

template<typename... Args>
class Function;

template<typename Ret, typename... Args>
class Function<Ret(Args...)> {

  class ICallable {
  public:
    virtual Ret operator()(Args...) = 0;
    virtual ~ICallable() = default;
  };

  template<typename T>
  class Callable : public ICallable {
  public:
    explicit Callable(T object) : object_(std::move(object)) {}

    Ret operator()(Args... args) override {
      return object_(args...);
      // return std::invoke(object_, std::forward<Args>(args)...);
    }

  private:
    T object_;
  };

public:
  template <typename T>
  Function(T object) : object_(new Callable<T>(std::move(object))) {  // NOLINT

  }
private:
  std::unique_ptr<ICallable> object_;
};

void Foo(int) {}

struct FuncObject {
  void operator()(int) {}
};

auto main() -> int {
  Function<void(int)> f = Foo;
  f = FuncObject{};
  f = [](int){};
//   Function<void(int, int, double, char)>;
}
// СМОТРИ И НАСЛАЖДАЙСЯ
// https://www.youtube.com/watch?v=dZ2qXPiTmkY&t=19s --- впендирюл без ферзя
// https://youtu.be/dQw4w9WgXcQ --- очень крутой видос
// https://youtu.be/o9lkjH8SkZ4 --- хорошая песня
// https://www.youtube.com/watch?v=EnQ6nndvYek --- финская полька
// https://s00.yaplakal.com/pics/pics_original/5/0/9/15894905.jpg
 --
