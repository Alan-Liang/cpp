#include <iostream>

using std::cin, std::cout, std::endl;


int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  panic::BPTree<int, int, 233> bpt{"file"};
  return 0;
}
