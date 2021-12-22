#ifdef X

#include <iostream>

using std::cin, std::cout, std::endl;


class UnrolledLinkedList {
 public:
  explicit UnrolledLinkedList (const std::string &filename, int nodesize = 316) :
    list_(filename),
    nodesize_(nodesize),
    maxNodesize_(2 * nodesize) {
    list_.seekg(0);
    list_.seekp(0);
    if (list_.peek() == EOF) {
      FirstNode tempFirst { 0, 0, nodesize_, maxNodesize_, 0 };
      list_.write(reinterpret_cast<char *>(&tempFirst), sizeof(tempFirst));
      list_.seekg(0);
      FirstNode a;
      list_.read(reinterpret_cast<char *>(&a), sizeof(a));
      std::cout << a.size << std::endl;
    } else {
      FirstNode tempFirst;
      list_.read(reinterpret_cast<char *>(&tempFirst), sizeof(tempFirst));
    }
  }
};


int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}

#endif

#include <bits/stdc++.h>

int main () {
  std::fstream fs {"file"};
  fs.seekg(0);
  fs.seekp(0);
  fs.peek();
  fs.clear();
  const char str[] = "hello";
  fs.write(str, 6);
}
