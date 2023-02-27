

template <typename T>
class AutoPtr {  //! фу-фу-фу
 public:

  explicit AutoPtr(T* ptr) : ptr_(ptr) {}

  ~AutoPtr() {
    delete ptr_;
  }

 private:
  T* ptr_;
};


int main() {
  AutoPtr<int> p(new int);
  auto pp = p;
}
