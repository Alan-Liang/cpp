#include<iostream>

#define MAXN 10001
#define MAXK 21
// don't know how to use error handling in C++, thus using goto
#define CHECK_BAD() if (badbit) goto badChar;
#define ROLLBACK() for (int j = 0; j < k; j++) array[backlog[j][0]] = backlog[j][1];
#define CHECK_BAD_AND_ROLLBACK() if (badbit) { ROLLBACK(); goto badChar; }

int array[MAXN];
int backlog[MAXK][2];
bool badbit = false;

inline int tryGetValue () {
  badbit = false;
  if (std::cin.peek() == ' ') std::cin.get();
  while (std::cin.peek() == '\r' || std::cin.peek() == '\n') std::cin.get();
  char c = std::cin.peek();
  if (c == EOF) return -1;
  if ((c < '0' || c > '9') && c != '-') {
    badbit = true;
    return -1;
  }
  int value;
  std::cin >> value;
  return value;
}

int main () {
  std::ios_base::sync_with_stdio(false);
  int length;
  std::cin >> length;
  for (int i = 0; i < length; i++) std::cin >> array[i];
  while (true) {
    mainLoop:
    int op = tryGetValue();
    if (std::cin.eof()) return 0;
    CHECK_BAD();
    if (op == 1) {
      int index = tryGetValue();
      CHECK_BAD();
      std::cout << array[index] << '\n';
      continue;
    }
    if (op == 2) {
      tryGetValue();
      CHECK_BAD();
    }
    int k = 0;
    while (true) {
      while (std::cin.peek() == ' ') std::cin.get();
      if (std::cin.peek() == '\r' || std::cin.peek() == '\n') break;
      int index = tryGetValue();
      CHECK_BAD_AND_ROLLBACK();
      while (std::cin.peek() == ' ') std::cin.get();
      if (std::cin.peek() == '\r' || std::cin.peek() == '\n') {
        std::cout << "Fail\n";
        ROLLBACK();
        goto mainLoop;
      }
      int value = tryGetValue();
      CHECK_BAD_AND_ROLLBACK();
      backlog[k][0] = index;
      backlog[k++][1] = array[index];
      array[index] = value;
    }
  }

  badChar:
  std::cout << "Bad\n";
  char c;
  while (c = std::cin.get()) if (c == '\r' || c == '\n' || c == EOF) break;
  goto mainLoop;
}
