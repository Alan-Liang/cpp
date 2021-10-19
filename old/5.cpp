#include<iostream>

int main () {
  int max = 0;
  int m;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    int current;
    std::cin >> current;
    if (current > max) max = current;
  }
  std::cout << max << std::endl;
}
