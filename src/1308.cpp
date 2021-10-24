#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>

using std::cin, std::cout, std::endl;

int main () {
  std::string type;
  char fill, background;
  int size;
  cin >> type >> fill >> background >> size;

  switch (type[0]) {
    case 'T': {
      int lines = (size + 1) / 2;
      for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < size; ++j) {
          int start = lines - i - 1;
          int end = size - start - 1;
          putchar(j < start || j > end ? background : fill);
        }
        putchar('\n');
      }
      break;
    }
    case 'S': {
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) putchar(fill);
        putchar('\n');
      }
      break;
    }
    case 'R': {
      if (size == 1) {
        putchar(fill);
        putchar('\n');
        break;
      }
      int lines = (size + 1) / 2;
      for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < size; ++j) {
          int start = lines - i - 1;
          int end = size - start - 1;
          putchar(j < start || j > end ? background : fill);
        }
        putchar('\n');
      }
      for (int i = lines - 2; i >= 0; --i) {
        for (int j = 0; j < size; ++j) {
          int start = lines - i - 1;
          int end = size - start - 1;
          putchar(j < start || j > end ? background : fill);
        }
        putchar('\n');
      }
      break;
    }
    default:
      assert(false);
  }

  return 0;
}
