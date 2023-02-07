//* RAII

class DynamicBloc {
  int* p_ = new int;

 public:

  ~DynamicBloc() {
    delete p_;
  }
};


int main() {
  DynamicBloc db;

  if (/**/) {
    return 0;
  } else {
    return 0;
  }

  return 0;
}
