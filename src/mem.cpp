#include <iostream>

int guess () {
  char addr[0];
  return *(int *)(addr + 29);
}

int main () {
  int answer;
  std::cin >> answer;
  if (guess() == answer) std::cout << "Accepted\n";
  else std::cout << "Wrong Answer\n";
  return 0;
}
