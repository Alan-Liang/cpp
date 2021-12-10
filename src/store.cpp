#include <cstdlib>
#include <iostream>
#include <fstream>

using std::cin, std::cout, std::endl;

struct content {
  int a;
  int b;
  char c[10];
};

int main () {
  std::fstream fs {"test", std::ios_base::out};
  // content *store = reinterpret_cast<content *>(malloc(sizeof(content)));
  // fs.read(reinterpret_cast<char *>(store), sizeof(content));
  // cout << store->a << " " << store->b << endl;
  content *c = new content { .a = 1, .b = 2 };
  fs.write(reinterpret_cast<const char *>(c), sizeof(content));
  fs.close();
  return 0;
}
