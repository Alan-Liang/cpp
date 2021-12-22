#include <climits>
#include <iostream>
#include <array>
#include <functional>
#include <cstring>
#include <fstream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unordered_map>
#include <set>
#include <string_view>

using std::cin, std::cout, std::endl;

char *minavail;

void *falloc (size_t n) {
  void *ret = minavail;
  minavail += n;
  return ret;
}

// https://en.cppreference.com/w/cpp/named_req/Allocator
template <class T>
struct Mallocator {
  typedef T value_type;
  Mallocator () = default;
  template <class U> constexpr Mallocator (const Mallocator <U>&) noexcept {}
  T *allocate (size_t n) { return static_cast<T *>(falloc(n * sizeof(T))); }
  void deallocate (T *p, size_t n) noexcept {}
};
template <class T, class U>
bool operator== (const Mallocator <T>&, const Mallocator <U>&) { return true; }
template <class T, class U>
bool operator!= (const Mallocator <T>&, const Mallocator <U>&) { return false; }

constexpr int sz = 1048576000;
using set = std::set<int, std::less<int>, Mallocator<int>>;
struct sstr {
  char c[66];
  operator std::string () const { return std::string(c); }
  sstr (const std::string &s) { strcpy(c, s.c_str()); }
  bool operator< (const sstr &that) const { return strcmp(c, that.c) < 0; }
  bool operator== (const sstr &that) const { return strcmp(c, that.c) == 0; }
};
using um = std::unordered_map<sstr, set *, std::hash<std::string>, std::equal_to<sstr>, Mallocator<std::pair<const sstr, set *>>>;

int main () {
  std::fstream fs;
  fs.open("data.o");
  bool init = false;
  if (!fs) {
    init = true;
    fs.close();
    fs.open("data.o", std::ios::out);
    fs.seekp(sz);
    fs.write("", 1);
    fs.close();
  }
  int fd = open("data.o", O_RDWR);
  void *ptr = (void *)(0x7fff'0000'0000);
  ptr = mmap(ptr, sz, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
  if (ptr == (void *)(-1)) {
    perror("mmap failed");
    return 1;
  }
  if (init) *((size_t *)ptr) = (size_t)ptr + 4096 * 10;
  minavail = *((char **)ptr);
  um &map = *(um *)((char *)ptr + 4096);
  if (init) new(&map) um;
  Mallocator<set> salloc;
  int n;
  cin >> n;
  while (n--) {
    std::string cmd, ix;
    int value;
    cin >> cmd >> ix;
    sstr six = ix;
    if (cmd == "insert") {
      cin >> value;
      set *s;
      if (!map.count(six)) {
        s = salloc.allocate(1);
        new(s) set;
        map[six] = s;
      } else s = map[six];
      s->insert(value);
    } else if (cmd == "delete") {
      cin >> value;
      if (!map.count(ix)) continue;
      map[ix]->erase(value);
    } else if (cmd == "find") {
      if (!map.count(ix)) {
        cout << "null\n";
        continue;
      }
      set &s = *map[ix];
      if (s.size() == 0) {
        cout << "null\n";
        continue;
      }
      for (const int &i : s) cout << i << ' ';
      cout << '\n';
    }
  }
  *((size_t *)ptr) = (size_t)minavail;
  munmap(ptr, sz);
  return 0;
}
