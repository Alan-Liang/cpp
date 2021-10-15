#include<iostream>

#define MAXN 10001

int array[MAXN];
char buf[MAXN];
int ops[21][2];

inline void bad () {
  std::cout << "Bad\n";
  std::cin.clear();
  std::cin.getline(buf, MAXN);
}
inline void fail () {
  std::cout << "Fail\n";
  std::cin.clear();
  std::cin.getline(buf, MAXN);
}

int main () {
  int length;
  std::cin >> length;
  for (int i = 0; i < length; i++) std::cin >> array[i];
  while (true) {
    mainLoop:
    int op;
    if (std::cin.eof()) return 0;
    std::cin >> op;
    if (std::cin.eof()) return 0;
    if (!std::cin.good()) { bad(); continue; }
    if (std::cin.eof()) return 0;
    if (op == 1) {
      int index;
      std::cin >> index;
      if (!std::cin.good()) { bad(); continue; }
      std::cout << array[index] << '\n';
      continue;
    }
    int _;
    if (op == 2) std::cin >> _;
    if (!std::cin.good()) { bad(); continue; }
    char c;
    int i = 0;
    while (true) {
      c = std::cin.get();
      if (!std::cin.good()) { bad(); goto mainLoop; }
      if (c == '\r' || c == '\n') break;
      int index, value;
      std::cin >> index;
      if (!std::cin.good()) { bad(); goto mainLoop; }
      c = std::cin.peek();
      if (c == '\r' || c == '\n') { fail(); goto mainLoop; }
      std::cin >> value;
      ops[i][0] = index;
      ops[i++][1] = value;
    }
    for (int j = 0; j < i; j++) array[ops[j][0]] = ops[j][1];
  }
}
