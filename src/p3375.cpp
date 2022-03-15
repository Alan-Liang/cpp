#include <cstdio>
#include <cstring>

constexpr int kMaxn = 1e6 + 10;

int common[kMaxn];
char self[kMaxn], pattern[kMaxn];
int lenSelf, lenPattern;

auto nextCommon (int i, char next) -> int {
  if (i == 0) return 0;
  if (next == pattern[common[i - 1]]) return common[i - 1] + 1;
  return nextCommon(common[i - 1], next);
}

auto generateCommon () -> void {
  for (int i = 1; i < lenPattern; ++i) common[i] = nextCommon(i, pattern[i]);
}

auto search () -> void {
  int posStart = 0;
  for (int i = 0; i < lenSelf; ++i) {
    if (self[i] == pattern[i - posStart]) {
      if (i - posStart == lenPattern - 1) {
        printf("%d\n", posStart + 1);
        posStart = i - common[i - posStart] + 1;
      }
      continue;
    }
    if (i == posStart) {
      ++posStart;
      continue;
    }
    posStart = i - common[i - posStart - 1];
    --i;
  }
}

auto main () -> int {
  scanf("%s%s", self, pattern);
  lenSelf = strlen(self);
  lenPattern = strlen(pattern);
  generateCommon();
  search();
  for (int i = 0; i < lenPattern; ++i) printf("%d ", common[i]);
  putchar('\n');
  return 0;
}
