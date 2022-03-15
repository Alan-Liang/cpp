#include <cstdio>

constexpr int kMaxn = 1e5 + 10;
int length;
struct {
  int prev;
  int next;
} pos[kMaxn];

auto main () -> int {
  scanf("%d", &length);
  pos[0].prev = pos[0].next = -1;
  int first = 0;
  for (int i = 1; i < length; ++i) {
    int ix, relative;
    scanf("%d%d", &ix, &relative);
    --ix;
    auto &cursor = pos[ix];
    auto &self = pos[i];
    if (relative == 0) {
      self.prev = cursor.prev;
      if (cursor.prev >= 0) pos[cursor.prev].next = i;
      self.next = ix;
      cursor.prev = i;
      if (self.prev == -1) first = i;
    } else {
      self.next = cursor.next;
      if (cursor.next >= 0) pos[cursor.next].prev = i;
      self.prev = ix;
      cursor.next = i;
    }
  }
  int cntRemove;
  scanf("%d", &cntRemove);
  for (int i = 0; i < cntRemove; ++i) {
    int id;
    scanf("%d", &id);
    --id;
    auto &self = pos[id];
    if (self.prev == -1) first = self.next;
    if (self.prev >= 0) pos[self.prev].next = self.next;
    if (self.next >= 0) pos[self.next].prev = self.prev;
    self.prev = self.next = -2;
  }
  while (first >= 0) {
    printf("%d ", first + 1);
    first = pos[first].next;
  }
  return 0;
}
