int complexCalculation () {
  int a = 1, b = 1, i = 0;
  while (++i < 100) {
    a = a + b;
    b = a + b;
  }
  return a;
}

int main () {
  int length = complexCalculation();
  int vla[length];
  for (int i = 0; i < length; ++i) vla[i] = 0xdeadbeef;
  return 0;
}
