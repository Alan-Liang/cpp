#include <iostream>

void throws () {
  throw 1;
}

void doesNotCatch () {
  throws();
  std::cout << "this would never happen!" << std::endl;
}

void catches () {
  try {
    doesNotCatch();
  } catch (int i) {
    std::cout << i << std::endl;
    throw i + 1;
  }
  std::cout << "this does not execute." << std::endl;
}

int main () {
  try {
    catches();
  } catch (int i) {
    std::cout << i << std::endl;
  }
  return 0;
}
