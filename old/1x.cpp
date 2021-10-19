#include<iostream>
#include<cstdio>

void checkSort (int a, int b, int c, int& A, int& B, int& C) {
  if (a <= b && a <= c) {
    A = a;
    if (b <= c) { B = b; C = c; }
    else { B = c; C = b; }
  }
}

void handleRequest (int A, int B, int C, const char* end) {
  char x = getchar();
  if (x == '\n') x = getchar();
  if (x == 'A') std::cout << A << end;
  if (x == 'B') std::cout << B << end;
  if (x == 'C') std::cout << C << end;
}

int main () {
  int a, b, c, t;
  std::cin >> a >> b >> c;
  int A, B, C;
  checkSort(a, b, c, A, B, C);
  t = a; a = b; b = t;
  checkSort(a, b, c, A, B, C);
  t = a; a = c; c = t;
  checkSort(a, b, c, A, B, C);

  handleRequest(A, B, C, " ");
  handleRequest(A, B, C, " ");
  handleRequest(A, B, C, "\n");
  return 0;
}
