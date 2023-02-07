class DynamicBloc {
  int* p_ = new int;

 public:

  DynamicBloc() = default;

  DynamicBloc(const DynamicBloc& object) : p_(new int) {
    *p_ = *object.p_;
  }

  DynamicBloc& operator=(const DynamicBloc& object) {
    if (&object == this) {
      return *this;
    }

    // CLear + Copy
    // Clear
    delete p_;

    // Copy
    p_ = new int;
    *p_ = *object.p_;

    return *this;

    // Copy & Swap
    // auto temp = object;
    // // swap(temp, *this);
    // swap(temp);

    // return *this;

  }

  ~DynamicBloc() {
    delete p_;
  }
};

//? What will happen?

int main() {
  DynamicBloc db;
  DynamicBloc db2;
  db2 = db;
  db = db;
}
