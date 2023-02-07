class DynamicBloc {
  int* p_ = new int;

 public:

  DynamicBloc() = default;

  DynamicBloc(const DynamicBloc& object) : p_(new int) {
    *p_ = *object.p_;
  }

  ~DynamicBloc() {
    delete p_;
  }
};

//? What will happen?

int main() {
  DynamicBloc db;
  auto db_copy = db;
}
