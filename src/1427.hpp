#include <unistd.h>
#include <iostream>
#include <memory>
#include <vector>

namespace panic {
void *malloc (size_t size) { return sbrk(size); }

// https://en.cppreference.com/w/cpp/named_req/Allocator
template <class T>
struct Mallocator {
  typedef T value_type;
  Mallocator () = default;
  template <class U> constexpr Mallocator (const Mallocator <U>&) noexcept {}
  T *allocate (size_t n) { return static_cast<T *>(malloc(n * sizeof(T))); }
  void deallocate (T *p, size_t n) noexcept {}
};
template <class T, class U>
bool operator== (const Mallocator <T>&, const Mallocator <U>&) { return true; }
template <class T, class U>
bool operator!= (const Mallocator <T>&, const Mallocator <U>&) { return false; }

struct {
  int next = 0;
  int operator() () { return next++; }
} nextId;
enum ArrayType { ARRAY, INT };
class Array {
 private:
  int id = nextId();
  ArrayType type_;
  using VecType = std::vector<Array *, Mallocator<Array *>>;
  std::shared_ptr<VecType> elements_;
  int value_;
  template <typename ...T>
  static Array *create (T ...args) {
    Array *array = reinterpret_cast<Array *>(malloc(sizeof(Array)));
    new(array) Array(args...);
    return array;
  }
 public:
  Array () : type_(ARRAY), elements_(std::allocate_shared<VecType>(Mallocator<VecType>())) {}
  Array (int value) : type_(INT), value_(value) {}
  void append (const Array &x) {
    if (x.type_ == INT) {
      elements_->push_back(create(x.value_));
      return;
    }
    elements_->push_back(create(x));
  }
  Array pop () {
    Array *back = elements_->back();
    elements_->pop_back();
    return *back;
  }
  Array &operator[] (size_t index) {
    return *(elements_->at(index));
  }
  operator int &() { return value_; }
  friend std::ostream &operator<< (std::ostream &os, const Array &array) {
    if (array.type_ == INT) return os << array.value_;
    os << '[';
    bool first = true;
    for (const auto &el : *array.elements_) {
      if (!first) os << ", ";
      first = false;
      if (el->id == array.id) {
        os << "[...]";
        continue;
      }
      os << *el;
    }
    os << ']';
    return os;
  }
};
} // namespace panic

using pylist = panic::Array;
