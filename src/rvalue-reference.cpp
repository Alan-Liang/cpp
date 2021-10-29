#include <cstdio>
#include <set>

using std::set;

int main () {
  set<int> a;
  set<int> &&b = (decltype(a)) a;
  return 0;
}
