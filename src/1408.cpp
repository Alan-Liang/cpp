#include <iostream>

using std::cin, std::cout, std::endl;

constexpr int kMaxHeight = 512;
constexpr int kMaxWidth = 512;
int height, width, sepHorizontal, sepVertical;
long long presum[kMaxHeight][kMaxWidth];

long long sumBlock (int i0, int j0, int i1, int j1) {
  return presum[i1][j1] - presum[i0 - 1][j1] - presum[i1][j0 - 1] + presum[i0 - 1][j0 - 1];
}

bool sepVPossible (int min, int i, int i1) {
  int j = 1;
  for (int sepVNow = 0; sepVNow < sepVertical; ++sepVNow) {
    int j1 = j;
    if (j1 > width) return false;
    while (true) {
      if (sumBlock(i, j, i1, j1) >= min) break;
      if (j1 >= width) return false;
      ++j1;
    }
    j = j1 + 1;
  }
  return true;
}

bool sepPossible (int min) {
  if (min == 0) return true;
  int i = 1;
  for (int sepHNow = 0; sepHNow < sepHorizontal; ++sepHNow) {
    int i1 = i;
    if (i1 > height) return false;
    while (true) {
      if (sepVPossible(min, i, i1)) break;
      if (i1 >= height) return false;
      ++i1;
    }
    i = i1 + 1;
  }
  return true;
}

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> height >> width >> sepHorizontal >> sepVertical;
  for (int i = 1; i <= height; ++i) {
    for (int j = 1; j <= width; ++j) {
      long long p;
      cin >> p;
      presum[i][j] = presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1] + p;
    }
  }
  int sum = presum[height][width];
  if (sepHorizontal == 1 && sepVertical == 1) cout << sum;
  int left = 0, right = sum;
  while (right > left) {
    int mid = (left + right) / 2;
    if (sepPossible(mid)) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  cout << left - 1 << endl;
  return 0;
}
