#include <cstdio>

constexpr int kMaxn = 2e5 + 10;

int next[kMaxn];
int data[kMaxn];
int first = 0;

auto advance (int k, int from) -> int {
  if (k == 0) return from;
  return advance(k - 1, next[from]);
}

auto main () -> int {
  int length, numOps;
  scanf("%d%d", &length, &numOps);
  int last = length;
  for (int i = 0; i < length; ++i) {
    scanf("%d", data + i);
    next[i] = i + 1;
  }
  for (int _ = 0; _ < numOps; ++_) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      ++length;
      int ix, num;
      scanf("%d%d", &ix, &num);
      --ix;
      if (ix < 0) {
        next[last] = first;
        data[last] = num;
        first = last++;
        continue;
      }
      int pos = advance(ix, first);
      next[last] = next[pos];
      next[pos] = last;
      data[last++] = num;
    } else {
      --length;
      int ix;
      scanf("%d", &ix);
      --ix;
      if (ix == 0) {
        first = next[first];
        continue;
      }
      if (ix == length) continue;
      int pos = advance(ix - 1, first);
      next[pos] = next[next[pos]];
    }
  }
  for (int i = 0; i < length; ++i) {
    printf("%d ", data[first]);
    first = next[first];
  }
  return 0;
}
