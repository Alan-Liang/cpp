#include <cstdio>
#include <cmath>

constexpr int kMaxn = 100010;

int length, cntQueries;
int st[kMaxn][17];

auto max (int a, int b) { return a > b ? a : b; }
auto min (int a, int b) { return a < b ? a : b; }

inline int get()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

auto read () -> void {
  length = get();
  cntQueries = get();
  for (int i = 0; i < length; ++i) st[i][0] = get();
}

auto prepare () -> void {
  int depth = log2(length);
  for (int i = 1; i <= depth; ++i) {
    int range = 1 << i;
    for (int j = 0; j < length - range + 1; ++j) {
      st[j][i] = max(st[j][i - 1], st[j + range / 2][i - 1]);
    }
  }
}

auto query (int l, int r) -> int {
  int dx = r - l + 1;
  int depth = log2(dx);
  int range = 1 << depth;
  int ddx = dx - range;
  return max(st[l][depth], st[l + ddx][depth]);
}

auto main () -> int {
  read();
  prepare();
  for (int i = 0; i < cntQueries; ++i) {
    int l = get();
    int r = get();
    printf("%d\n", query(l - 1, r - 1));
  }

  return 0;
}
