#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

#ifdef DEBUG
#include <iostream>
#define _log(x) std::clog << x << std::endl;
#else
#define _log(x)
#endif

namespace panic {

template <typename T>
struct less {
  auto operator() (const T &a, const T &b) -> bool {
    return a < b;
  }
};

template <typename T, class Compare = panic::less<T>>
class PairingHeap {
 public:
  struct Node {
    T value;
    Node *firstChild = nullptr;
    Node *neighbor = nullptr;

    Node (const T &value) : value(value) {}
    Node (const Node &other) : value(other.value) {
      // _log("PairingHeap::Node::Node(const Node&)");
      if (other.firstChild != nullptr) firstChild = new Node(*other.firstChild);
      if (other.neighbor != nullptr) neighbor = new Node(*other.neighbor);
    }
    auto destroy () -> void {
      if (firstChild != nullptr) {
        firstChild->destroy();
        delete firstChild;
      }
      if (neighbor != nullptr) {
        neighbor->destroy();
        delete neighbor;
      }
    }
  };

  Compare less;
  Node *root = nullptr;

  /// merges two trees and returns the new root.
  auto mergeRoots (Node *a, Node *b) -> Node * {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (less(a->value, b->value)) std::swap(a, b);
    // a >= b here
    // since b is a tree root, it could not have a neighbor
    b->neighbor = a->firstChild;
    a->firstChild = b;
    return a;
  }

  /// merges all the children of the root node and returns the new root.
  auto mergeChildren (Node *firstChild) -> Node * {
    if (firstChild == nullptr) return nullptr;
    Node *secondChild = firstChild->neighbor;
    if (secondChild == nullptr) return firstChild;
    Node *thirdChild = secondChild->neighbor;
    firstChild->neighbor = secondChild->neighbor = nullptr;
    return mergeRoots(mergeRoots(firstChild, secondChild), mergeChildren(thirdChild));
  }

  PairingHeap () = default;
  PairingHeap (const PairingHeap &other) { *this = other; }
  ~PairingHeap () {
    if (root != nullptr) root->destroy();
    delete root;
  }
  auto operator= (const PairingHeap &other) -> PairingHeap & {
    if (this == &other) return *this;
    if (root != nullptr) {
      root->destroy();
      delete root;
      root = nullptr;
    }
    if (other.root != nullptr) root = new Node(*other.root);
    return *this;
  }
};

} // namespace panic

namespace sjtu {

template <typename T, class Compare = panic::less<T>>
class priority_queue {
 public:
  priority_queue () = default;
  /**
   * get the top of the queue.
   * @return a reference of the top element.
   * throw container_is_empty if empty() returns true;
   */
  auto top () const -> const T & {
    return heap_.root->value;
  }
  /// push new element to the priority queue.
  auto push (const T &value) -> void {
    Node *newNode = new Node(value);
    heap_.root = heap_.mergeRoots(heap_.root, newNode);
    ++size_;
  }
  /**
   * delete the top element.
   * throw container_is_empty if empty() returns true;
   */
  auto pop () -> void {
    Node *firstChild = heap_.root->firstChild;
    delete heap_.root;
    heap_.root = heap_.mergeChildren(firstChild);
    --size_;
  }
  /// return the number of the elements.
  auto size () const -> size_t { return size_; }
  /**
   * check if the container has at least an element.
   * @return true if it is empty, false if it has at least an element.
   */
  auto empty () const -> bool { return size_ == 0; }
  /**
   * merge two priority_queues with at ~~least~~ most O(logn) complexity.
   * clear the other priority_queue.
   */
  auto merge (priority_queue &other) -> void {
    size_ += other.size_;
    other.size_ = 0;
    heap_.root = heap_.mergeRoots(heap_.root, other.heap_.root);
    other.heap_.root = nullptr;
  }

 private:
  using Heap = panic::PairingHeap<T, Compare>;
  using Node = typename Heap::Node;
  Heap heap_;
  size_t size_ = 0;
};

}

auto nextInt () -> int;
auto readN (int *array, int n) -> void;
template <typename T>
auto print (const T &) -> void;
template <typename T>
auto println (const T &) -> void;
template <typename T>
auto printsp (const T &) -> void;

const int kMaxn = 1e5 + 10;
const int kMaxm = 1e3 + 10;

struct Node {
  Node *childs = nullptr;
  long long weight = 0;
  auto operator< (const Node &rhs) const -> bool {
    return weight > rhs.weight;
  }
};

int cntBranches, length;
sjtu::priority_queue<Node> q;


auto sum (const Node &root, int depth) -> long long {
  if (root.childs == nullptr) return (depth - 1) * root.weight;
  long long res = 0;
  for (int i = 0; i < cntBranches; ++i) {
    res += sum(root.childs[i], depth + 1);
  }
  return res;
}


auto main () -> int {
  length = nextInt();
  cntBranches = nextInt();
  for (int i = 0; i < length; ++i) {
    q.push({ nullptr, nextInt() });
  }
  int cntPadding = cntBranches - (length - 1) % (cntBranches - 1) - 1;
  if (cntPadding == cntBranches - 1) cntPadding = 0;
  for (int i = 0; i < cntPadding; ++i) q.push({ nullptr, 0 });
  while (q.size() > 1) {
    Node currentNode;
    currentNode.childs = new Node[cntBranches];
    for (int i = 0; i < cntBranches; ++i) {
      currentNode.childs[i] = q.top();
      q.pop();
      currentNode.weight += currentNode.childs[i].weight;
    }
    q.push(currentNode);
  }
  const Node &root = q.top();
  println(sum(root, 1));
  return 0;
}




auto nextInt () -> int {
  int i = 0, sign = 1;
  char c;
  while (!isdigit(c = getchar())) if (c == '-') sign = -1;
  do {
    i = i * 10 + c - '0';
  } while (isdigit(c = getchar()));
  return i * sign;
}

auto readN (int *array, int n) -> void {
  for (int i = 0; i < n; ++i) array[i] = nextInt();
}

template <>
auto print<int> (const int &val) -> void {
  printf("%d", val);
}
template <>
auto print<char> (const char &val) -> void {
  putchar(val);
}
template <>
auto print<char *> (char * const &val) -> void {
  printf("%s", val);
}
template <>
auto print<const char *> (const char * const &val) -> void {
  printf("%s", val);
}
template <>
auto print<long long> (const long long &val) -> void {
  printf("%lld", val);
}
template <>
auto print<unsigned long long> (const unsigned long long &val) -> void {
  printf("%llu", val);
}
template <typename T>
auto println (const T &val) -> void {
  print(val);
  putchar('\n');
}
template <typename T>
auto printsp (const T &val) -> void {
  print(val);
  putchar(' ');
}
