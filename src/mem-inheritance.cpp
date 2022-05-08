struct Base {
  int a = 0x1234;
};
struct Derived : public Base {
  int b = 0x5678;
};

auto main () -> int {
  Derived d;
  return 0;
}
