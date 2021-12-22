#include "multi.h"
#include "multi.1.h"

int f () {
  C<233> c;
  C<817> c1;
  volatile int x = c.f();
  return 0;
}
