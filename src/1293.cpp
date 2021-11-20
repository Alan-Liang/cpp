#include <cassert>
#include <iostream>

#include <unordered_map>

#define DEBUG_(...) sizeof(0)

namespace panic {
template <typename T>
class WeakRef {
 private:
  static std::unordered_map<T *, int> cntRefs_;
 public:
  T *ptr = nullptr;
  WeakRef (T *ptr) { set(ptr); }
  ~WeakRef () { reset(); }
  void set (T *next) {
    DEBUG_(std::cerr << "set" << (next ? *next : (T)0) << std::endl);
    if (next == nullptr) return;
    ptr = next;
    if (cntRefs_.count(ptr) == 0) cntRefs_[ptr] = 0;
    ++(cntRefs_[ptr]);
  }
  void reset () {
    DEBUG_(std::cerr << "reset" << (ptr ? *ptr : (T)0) << std::endl);
    if (ptr == nullptr) return;
    --(cntRefs_[ptr]);
    if (cntRefs_[ptr] == 0) {
      cntRefs_.erase(ptr);
      DEBUG_(std::cerr << "delete" << *ptr << std::endl);
      delete ptr;
    }
  }
  void reset (T *next) {
    if (next == ptr) return;
    DEBUG_(std::cerr << "reset2" << (ptr ? *ptr : (T)0) << std::endl);
    reset();
    set(next);
  }
};
template <typename T>
std::unordered_map<T *, int> WeakRef<T>::cntRefs_;

template <typename T>
class shared_ptr {
 private:
  WeakRef<T> ref_;
 public:
  shared_ptr () : ref_(nullptr) {}
  shared_ptr (const shared_ptr &ptr) : ref_(ptr.ref_.ptr) {}
  shared_ptr (T *ptr) : ref_(ptr) {}
  T &operator* () const { return *(ref_.ptr); }
  shared_ptr &operator= (const shared_ptr &other) { ref_.reset(other.ref_.ptr); return *this; }
  void reset () { ref_.reset(); }
  void reset (T *ptr) { ref_.reset(ptr); }
};
} // namespace panic

using shared_ptr = panic::shared_ptr<int>;

using namespace std;

int main () {
  const shared_ptr p(new int(-1));
  cout << *p << endl;
  shared_ptr pp(p);
  cout << *pp << endl;
  *pp = 6;
  cout << *pp << endl;
  cout << *p << endl;
  pp.reset();


  shared_ptr p2;
  p2.reset( new int(4));
  *p2 = 5;
  cout << *p2 << endl;
  p2.reset();

  shared_ptr p3(new int(1));
  int *x = new int(4);
  shared_ptr p4(x);

  int *y = new int(4);
  shared_ptr p5(y);
  shared_ptr p6(p5);
  shared_ptr p7(shared_ptr(shared_ptr(new int(1))));
  shared_ptr p8(new int(4));
  p8 = p8;
  p8 = p7;
  p8 = p6;
  p8 = p5;


  int *z = new int(4);
  shared_ptr p9(z);
  p9 = p9;
  auto p10 = p9;
  p9 = p10;

  int *a = new int(4);
  shared_ptr p11(a);
  shared_ptr p12(p11);
  *p11 += 1;
  cout << *p12 << endl;
  p12.reset(new int(5));
  *p12 += 2;
  cout << *p12 << endl;
}
