#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

constexpr int kMaxn = 4e6 + 10;

struct Cmd {
  union {
    struct {
      int i, j, e;
    };
    int v[3];
  };
};
Cmd cmd[kMaxn];

template <typename T>
auto sort (T *array, int l, int r) -> void {
  if (r - l <= 1) return;
  int mid = (l + r) / 2;
  sort(array, l, mid);
  sort(array, mid, r);
  T tmp[r - l + 1];
  int s = 0;
  int p = l;
  int q = mid;
  while (s < r - l) {
    if (p < mid && (q >= r || array[p] < array[q])) {
      tmp[s] = array[p];
      ++s; ++p;
    } else {
      tmp[s] = array[q];
      ++s; ++q;
    }
  }
  for (int i = 0; i < r - l; ++i) array[i + l] = tmp[i];
}

int ih[2 * kMaxn];

int set[2 * kMaxn];

template <typename T>
auto lower (T *l, T *r, T target) -> T * {
  int d = r - l;
  while (d > 0) {
    int mid = d / 2;
    auto p = l + mid;
    if (target > *p) {
      ++p;
      l = p;
      d -= mid + 1;
    } else {
      d = mid;
    }
  }
  return l;
}

auto hash (int i) -> int {
  return (i ^ 921409321) % (2 * kMaxn);
}
auto hput (int x) -> void {
  for (int i = hash(x);; ++i) {
    if (ih[i] == 0) {
      ih[i] = x;
      break;
    }
    if (i == 2 * kMaxn - 1) i = -1;
  }
}
auto hget (int x) -> int {
  for (int i = hash(x);; ++i) {
    if (ih[i] == x) return i;
    if (ih[i] == 0) {
      ih[i] = x;
      set[i] = i;
      return i;
    }
    if (i == 2 * kMaxn - 1) i = -1;
  }
}

auto setGet (int i) -> int {
  if (set[i] == i) return i;
  return set[i] = setGet(set[i]);
}
auto setUnion (int a, int b) -> void {
  int s1 = setGet(a), s2 = setGet(b);
  set[s1] = s2;
}

auto nextInt () -> int {
  int n = 0, s = 1;
  char c;
  while (!isdigit(c = getchar())) if (c == '-') s = -1;
  do {
    n = n * 10 + c - '0';
  } while (isdigit(c = getchar()));
  return n * s;
}

auto main () -> int {
  int t = nextInt();
  for (int i = 0; i < t; ++i) {
    memset(ih, 0, sizeof(ih));
    int n = nextInt();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 3; ++j) {
        cmd[i].v[j] = nextInt();
      }
      cmd[i].i = hget(cmd[i].i);
      cmd[i].j = hget(cmd[i].j);
    }
    for (int i = 0; i < n; ++i) {
      auto &c = cmd[i];
      if (c.e == 1) setUnion(c.i, c.j);
    }
    bool s = true;
    for (int i = 0; i < n; ++i) {
      auto &c = cmd[i];
      if (c.e == 0) if (setGet(c.i) == setGet(c.j)) {
        s = false;
        break;
      }
    }
    printf(s ? "YES\n" : "NO\n");
  }
  return 0;
}
