//! NO GOD! PLEASE NO!!! NOOOOOOOOOO

class DynamicBloc {
  int* p_ = new int;

 public:

  void Clear() {
    delete p_;
  }
};


int main() {
  DynamicBloc db;
  DynamicBloc db1;
  DynamicBloc db2;

  if (/**/) {
    goto clear;
  } else {
    goto clear;
  }

clear:

  db.Clear();
  db1.Clear();
  db2.Clear();
  return 0;
}
