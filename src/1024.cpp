#include "1024.hpp"

#define MAXN 10000

char playground[MAXN];
void *ptr[MAXN];

auto main () -> int {
  for (int i = 0; i < MAXN; i++) {
    playground[i] = -1;
  }

  MemoryPoolManager mm(playground, 64, MAXN / 64);
  for (int i = 0; i < MAXN; i++) ptr[i] = mm.allocate();
  mm.free(ptr[20]);
  for (int i = 0; i < MAXN; i++) mm.free(mm.allocate());
  ptr[21] = mm.allocate();
  return 0;
}
