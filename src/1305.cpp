#include<iostream>

#define MAXN 10001

int array[MAXN];

int main () {
  std::ios_base::sync_with_stdio(false);
  int length;
  std::cin >> length;
  for (int i = 0; i < length; i++) std::cin >> array[i];
  while (true) {
    int op;
    std::cin >> op;
    if (std::cin.eof()) return 0;
    if (op == 1) {
      int index;
      std::cin >> index;
      std::cout << array[index] << '\n';
      continue;
    }
    int _;
    if (op == 2) std::cin >> _;
    char c;
    while (true) {
      c = std::cin.get();
      // TODO: 行末空格 Lookahead
      if (c == '\r' || c == '\n') break;
      int index, value;
      std::cin >> index >> value;
      array[index] = value;
    }
  }
}