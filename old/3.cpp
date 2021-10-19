#include<iostream>

#define printxb 

int main () {
  int x, m, op, num;
  std::cin >> x >> m;
  for (int i = 0; i < m; i++) {
    std::cin >> op >> num;
    switch (op) {
      case 0: x = num; std::cout << x << std::endl; break;
      case 1: x += num; std::cout << x << std::endl; break;
      case 2: x -= num; std::cout << x << std::endl; break;
      case 3: x *= num; std::cout << x << std::endl; break;
      case 4: x /= num; std::cout << x << std::endl; break;
      case 5: x %= num; std::cout << x << std::endl; break;
      case 6: std::cout << x-- << std::endl; break;
      case 7: std::cout << --x << std::endl; break;
      case 8: std::cout << x++ << std::endl; break;
      case 9: std::cout << ++x << std::endl; break;
    }
  }
  std::cout << x << std::endl;
}
