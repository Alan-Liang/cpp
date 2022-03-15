#include <cstdio>
#include <cstring>

constexpr int kMaxn = 1e6 + 10;

int common[kMaxn];
char pattern[kMaxn];
int lenPattern;

auto nextCommon (int i, char next, bool print = false) -> int {
  if (i == 0) return 0;
  if (next == pattern[common[i - 1]]) return common[i - 1] + 1;
  int res = nextCommon(common[i - 1], next, print);
  if (print) printf("%d\n", i);
  return res;
}

auto generateCommon () -> void {
  for (int i = 1; i < lenPattern; ++i) common[i] = nextCommon(i, pattern[i]);
}

auto main () -> int {
  scanf("%s", pattern);
  lenPattern = strlen(pattern);
  generateCommon();
  nextCommon(lenPattern, '\0', true);
  return 0;
}
