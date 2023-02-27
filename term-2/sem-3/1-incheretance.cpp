struct Animal {
  void Walk();
};

struct Mammals : Animal {
  void Bite();
};

struct Bird : Animal {
  void Fly();
};

struct Cat : Mammals {
  void Sound();
};

struct Dog : Mammals {
  void Sound();
};

struct Parrot : Bird {
  void Sound();
};
