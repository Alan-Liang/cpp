#include <cstdio>

int main () {
  int state = 0;
  char c;
  bool hasPendingWhitespace = false;
  bool hasData = false;
  while ((c = getchar()) != EOF) {
    if (c == '\n') ++state;
    if (state < 2) continue;
    if (c == '\n' || c == ' ') {
      if (hasData) hasPendingWhitespace = true;
      continue;
    }
    if (hasPendingWhitespace) {
      hasPendingWhitespace = false;
      putchar(' ');
    }
    hasData = true;
    putchar(c);
  }
  putchar('\n');
  return 0;
}
