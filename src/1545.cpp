#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

auto nextInt () -> int;
auto readN (int *array, int n) -> void;
template <typename T>
auto print (const T &) -> void;
template <typename T>
auto println (const T &) -> void;
template <typename T>
auto printsp (const T &) -> void;
template <typename T>
struct Greater;
template <typename T>
struct Less;

constexpr int kMaxn = 6e3 + 10;
int arr[kMaxn][kMaxn];
int width, height, sz;

auto lowbit (int x) -> int {
  return x & -x;
}
struct Point {
  int x, y;
  auto transform () const -> Point {
    return { x + y - 1, width - x + y };
  }
};
auto presum (Point p) -> int {
  int ans = 0;
  while (p.x >= 1) {
    int y = p.y;
    while (y >= 1) {
      ans += arr[p.x][y];
      y -= lowbit(y);
    }
    p.x -= lowbit(p.x);
  }
  return ans;
}
auto add (Point p, int dx) -> void {
  while (p.x <= sz) {
    int y = p.y;
    while (y <= sz) {
      arr[p.x][y] += dx;
      y += lowbit(y);
    }
    p.x += lowbit(p.x);
  }
}
auto rectsum (Point l, Point r) -> int {
  --l.x; --l.y;
  return presum(r) - presum({ l.x, r.y }) - presum({ r.x, l.y }) + presum(l);
}

auto main () -> int {
  width = nextInt();
  height = nextInt();
  sz = width + height - 1;
  for (int i = 1; i <= height; ++i) {
    for (int j = 1; j <= width; ++j) {
      add((Point){ i, j }.transform(), nextInt());
    }
  }
  while (true) {
    int op = nextInt(), y = nextInt(), x = nextInt();
    if (op == -1) return 0;
    if (op == 1) {
      add((Point){ x, y }.transform(), nextInt());
    } else {
      int a = nextInt();
      println(rectsum((Point){ x, y - a }.transform(), (Point){ x, y + a }.transform()));
    }
  }
  return 0;
}




auto nextInt () -> int {
    char ch = getchar();
    if (ch == EOF) return -1;
    int x = 0, f = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
        if (ch == EOF) return -1;
    }
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

auto readN (int *array, int n) -> void {
  for (int i = 0; i < n; ++i) array[i] = nextInt();
}

template <>
auto print<int> (const int &val) -> void {
  printf("%d", val);
}
template <>
auto print<char> (const char &val) -> void {
  putchar(val);
}
template <>
auto print<char *> (char * const &val) -> void {
  printf("%s", val);
}
template <>
auto print<const char *> (const char * const &val) -> void {
  printf("%s", val);
}
template <>
auto print<long long> (const long long &val) -> void {
  printf("%lld", val);
}
template <>
auto print<unsigned long long> (const unsigned long long &val) -> void {
  printf("%llu", val);
}
template <typename T>
auto println (const T &val) -> void {
  print(val);
  putchar('\n');
}
template <typename T>
auto printsp (const T &val) -> void {
  print(val);
  putchar(' ');
}
template <typename T>
struct Greater {
  auto operator() (const T &lhs, const T &rhs) const -> bool {
    return lhs > rhs;
  }
};

template <typename T>
struct Less {
  auto operator() (const T &lhs, const T &rhs) const -> bool {
    return lhs < rhs;
  }
};
