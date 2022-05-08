#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using std::cin, std::cout, std::endl;

constexpr int kMaxn = 1e6 + 10;
constexpr int kMaxi = 1e6 + 10;

int common[kMaxn];
std::string self;
std::string patterns[kMaxi];

auto clear () -> void {
  memset(common, 0, sizeof(common));
}

auto nextCommon (const std::string &str, int pos, char next) -> int {
  if (pos == 0) return 0;
  if (str[common[pos - 1]] == next) return common[pos - 1] + 1;
  return nextCommon(str, common[pos - 1], next);
}

auto gen (const std::string &str) -> void {
  clear();
  for (int i = 0; i < str.length(); ++i) common[i] = nextCommon(str, i, str[i]);
}

auto query (const std::string &pattern) -> bool {
  gen(pattern);
  int posStart = 0;
  for (int i = 0; i < self.length(); ++i) {
    if (self[i] == pattern[i - posStart]) {
      if (i - posStart == pattern.length() - 1) {
        return true;
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
  return false;
}

auto main () -> int {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) cin >> patterns[i];
  cin >> self;
  bool has = false;
  for (int i = 0; i < n; ++i) {
    if (query(patterns[i])) {
      has = true;
      break;
    }
  }
  printf(has ? "valar morghulis\n" : "valar dohaeris\n");
  return 0;
}
