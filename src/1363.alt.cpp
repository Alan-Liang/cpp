#include <iostream>
#include <string>

using std::cin, std::cout, std::endl;

#include <list>
#include <cassert>
namespace panic {
/// Doubly linked list.
template <typename ValueType>
class List {
 private:
  std::list<ValueType> l_;
 public:
  void push_back (const ValueType &value) {
    l_.push_back(value);
  }
  void pop_back () {
    assert(!l_.empty()); // ok
    l_.pop_back();
  }
  void push_front (const ValueType &value) {
    l_.push_front(value);
  }
  void pop_front () {
    assert(!l_.empty()); // ok
    l_.pop_front();
  }
  ValueType &front () const {
    assert(!l_.empty()); // ok
    return const_cast<List *>(this)->l_.front();
  }
  ValueType &back () const {
    assert(!l_.empty()); // ok
    return const_cast<List *>(this)->l_.back();
  }
  void insert (int index, const ValueType &value) {
    auto it = l_.begin();
    assert(index >= 0); // !!!
    assert(index <= l_.size()); // !!!
    std::advance(it, index);
    l_.insert(it, value);
  }
  void erase (int index) {
    assert(!l_.empty()); // ok
    assert(index >= 0); // !!!
    assert(index < l_.size()); // !!!
    auto it = l_.begin();
    std::advance(it, index);
    l_.erase(it);
  }
  int size () const { return l_.size(); }
  bool empty () const { return l_.empty(); }
  void clear () {
    l_.clear();
  }

  void link (const List &append) {
    std::list copy = append.l_;
    l_.splice(l_.end(), copy);
  }
  List cut (int index) {
    assert(index >= 0); // ok
    assert(index <= l_.size()); // ok
    List newList;
    auto it = l_.begin();
    std::advance(it, index);
    newList.l_.splice(newList.l_.end(), l_, it, l_.end());
    return newList;
  }
  void print () {
    std::cout << "[DEBUG]";
    for (const auto &x : l_) std::cout << ' ' << x;
    std::cout << std::endl;
  }
};
} // namespace panic

template <typename T>
using MyList = panic::List<T>;

class Move {
 public:
  Move () {
    std::cout << "ctor" << std::endl;
  }
  Move (const Move &) {
    std::cout << "copy ctor" << std::endl;
  }
  Move (Move &&) noexcept {
    std::cout << "move ctor" << std::endl;
  }
  constexpr Move &operator= (const Move &) = default;
};

int main () {
  // std::ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  // MyList<std::string> ll1;
  // for (const char *i : { "a", "b", "c", "d", "e", "f", "g" }) ll1.push_back(i);
  // ll1.printx();
  // auto llx = ll1.cut(ll1.size());
  // llx.printx();
  // llx.link(ll1);
  // llx.printx();
  // ll1.printx();
#ifdef DEBUG
  #include "1363.in"
#endif
  // MyList<int> x = MyList<int>(std::move(x));
  return 0;
}
