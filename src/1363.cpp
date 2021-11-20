#include <iostream>
#include <string>

using std::cin, std::cout, std::endl;

namespace panic {
template <typename ValueType>
struct ListNode {
  ListNode<ValueType> *prev = nullptr;
  ListNode<ValueType> *next = nullptr;
  ValueType value;
};

/// Doubly linked list.
template <typename ValueType>
class List {
 private:
  using NodeType = ListNode<ValueType>;
  NodeType begin_ {};
  NodeType end_ {};
  int size_ = 0;
  void init_ () {
    begin_.next = &end_;
    end_.prev = &begin_;
  }
  void destroy_ () {
    if (size_ == 0) return;
    NodeType *current = begin_.next;
    while (current != &end_) {
      NodeType *toBeDeleted = current;
      current = toBeDeleted->next;
      delete toBeDeleted;
    }
    size_ = 0;
  }
 public:
  List () { init_(); }
  List (List &&obj) noexcept : begin_(std::move(obj.begin_)), end_(std::move(obj.end_)), size_(obj.size_) {
    if (obj.size_ == 0) {
      begin_.next = &end_;
      end_.prev = &begin_;
    }
    obj.size_ = 0;
    begin_.next->prev = &begin_;
    end_.prev->next = &end_;
  }
  List (const List &foreign) : size_(foreign.size_) {
    if (&foreign == this) {
      size_ = 0;
      init_();
      return;
    }
    NodeType *foreignPrevNode = const_cast<NodeType *>(&(foreign.begin_));
    NodeType *prevNode = &begin_;
    while (foreignPrevNode->next != &(foreign.end_)) {
      NodeType *foreignThisNode = const_cast<NodeType *>(foreignPrevNode->next);
      NodeType *thisNode = new NodeType;
      thisNode->value = foreignThisNode->value;
      thisNode->prev = prevNode;
      prevNode->next = thisNode;
      foreignPrevNode = foreignThisNode;
      prevNode = thisNode;
    }
    prevNode->next = &end_;
    end_.prev = prevNode;
  }
  ~List () { destroy_(); }

  void push_back (const ValueType &value) {
    NodeType *newNode = new NodeType;
    newNode->value = value;
    newNode->next = &end_;
    NodeType *prevNode = end_.prev;
    newNode->prev = prevNode;
    prevNode->next = newNode;
    end_.prev = newNode;
    ++size_;
  }
  void pop_back () {
    NodeType *toBeDeleted = end_.prev;
    NodeType *prevNode = toBeDeleted->prev;
    prevNode->next = &end_;
    end_.prev = prevNode;
    delete toBeDeleted;
    --size_;
  }
  void push_front (const ValueType &value) {
    NodeType *newNode = new NodeType;
    newNode->value = value;
    newNode->prev = &begin_;
    NodeType *nextNode = begin_.next;
    newNode->next = nextNode;
    nextNode->prev = newNode;
    begin_.next = newNode;
    ++size_;
  }
  void pop_front () {
    NodeType *toBeDeleted = begin_.next;
    NodeType *nextNode = toBeDeleted->next;
    nextNode->prev = &begin_;
    begin_.next = nextNode;
    delete toBeDeleted;
    --size_;
  }
  ValueType &front () const { return begin_.next->value; }
  ValueType &back () const { return end_.prev->value; }
  void insert (int index, const ValueType &value) {
    NodeType *prevNode = &begin_;
    while (index--) prevNode = prevNode->next;
    NodeType *thisNode = new NodeType;
    thisNode->value = value;
    NodeType *nextNode = prevNode->next;
    prevNode->next = thisNode;
    thisNode->next = nextNode;
    nextNode->prev = thisNode;
    thisNode->prev = prevNode;
    ++size_;
  }
  void erase (int index) {
    NodeType *prevNode = &begin_;
    while (index--) prevNode = prevNode->next;
    NodeType *thisNode = prevNode->next;
    NodeType *nextNode = thisNode->next;
    nextNode->prev = prevNode;
    prevNode->next = nextNode;
    delete thisNode;
    --size_;
  }
  int size () const { return size_; }
  bool empty () const { return size_ == 0; }
  void clear () {
    destroy_();
    init_();
  }

  void link (const List &append) {
    if (&append == this) {
      if (size_ == 0) return;
      if (size_ == 1) {
        push_back(back());
        return;
      }
      NodeType *origBack = end_.prev;
      NodeType *prevNode = end_.prev;
      for (NodeType *foreignThisNode = begin_.next; foreignThisNode->prev != origBack; foreignThisNode = foreignThisNode->next) {
        NodeType *thisNode = new NodeType;
        thisNode->value = foreignThisNode->value;
        thisNode->prev = prevNode;
        prevNode->next = thisNode;
        thisNode->next = &end_;
        prevNode = thisNode;
      }
      end_.prev = prevNode;
      size_ *= 2;
      return;
    }
    NodeType *prevNode = end_.prev;
    for (NodeType *foreignThisNode = append.begin_.next; foreignThisNode != &(append.end_); foreignThisNode = foreignThisNode->next) {
      NodeType *thisNode = new NodeType;
      thisNode->value = foreignThisNode->value;
      thisNode->prev = prevNode;
      prevNode->next = thisNode;
      thisNode->next = &end_;
      prevNode = thisNode;
    }
    end_.prev = prevNode;
    size_ += append.size_;
  }
  List cut (int index) {
    List newList {};
    newList.size_ = size_ - index;
    size_ = index;
    NodeType *prevNode = &begin_;
    while (index--) prevNode = prevNode->next;
    if (prevNode->next == &end_) return newList;
    NodeType *newFirst = newList.begin_.next = prevNode->next;
    prevNode->next = &end_;
    NodeType *newLast = newList.end_.prev = end_.prev;
    end_.prev = prevNode;
    newFirst->prev = &(newList.begin_);
    newLast->next = &(newList.end_);
    return newList;
  }
  void print () {
    std::cout << "[DEBUG]";
    for (NodeType *current = begin_.next; current != &end_; current = current->next) std::cout << ' ' << current->value;
    std::cout << std::endl;
  }
  void printx () {
    std::cout << "[DEBUG]";
    for (NodeType *current = begin_.next; current != &end_; current = current->next) std::cout << ' ' << (size_t)current;
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
  MyList<std::string> ll1;
  for (const char *i : { "a", "b", "c", "d", "e", "f", "g" }) ll1.push_back(i);
  ll1.printx();
  auto llx = ll1.cut(ll1.size());
  llx.printx();
  llx.link(ll1);
  llx.printx();
  ll1.printx();
#ifdef DEBUG
  // #include "1363.in"
#endif
  // MyList<int> x = MyList<int>(std::move(x));
  return 0;
}
