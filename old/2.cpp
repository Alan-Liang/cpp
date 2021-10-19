#include<cstdio>

int _xor (int a, int b) { return a == b ? 0 : 1; }
int _and (int a, int b) { return a == 1 && b == 1 ? 1 : 0; }
int _or (int a, int b) { return a == 1 || b == 1 ? 1 : 0; }

int scan () { return getchar() == '1' ? 1 : 0;  }
void halfAdder (int a, int b, int& out, int& carry) {
  out = _xor(a, b);
  carry = _and(a, b);
}
void fullAdder (int a, int b, int carryIn, int &out, int &carryOut) {
  int carry, carry2, intermediate;
  halfAdder(a, b, intermediate, carry);
  halfAdder(intermediate, carryIn, out, carry2);
  carryOut = _or(carry, carry2);
}
int main () {
  int a[4];
  int b[4];
  a[0] = scan();
  a[1] = scan();
  a[2] = scan();
  a[3] = scan();
  scan(); // \n
  b[0] = scan();
  b[1] = scan();
  b[2] = scan();
  b[3] = scan();
  int res[4];
  int carry[4];
  fullAdder(a[3], b[3], 0, res[3], carry[3]);
  fullAdder(a[2], b[2], carry[3], res[2], carry[2]);
  fullAdder(a[1], b[1], carry[2], res[1], carry[1]);
  fullAdder(a[0], b[0], carry[1], res[0], carry[0]);
  printf("%d%d%d%d\n", res[0], res[1], res[2], res[3]);
}
