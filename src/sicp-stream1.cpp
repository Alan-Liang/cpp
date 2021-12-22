#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
// 如果你不想手写 std::list:
// #include <list>

using std::cin, std::cout, std::endl;

// 你可以直接把 1363. Linklist Without Name 的代码搬过来

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
  void clear () {
    destroy_();
    init_();
  }

  const ValueType &nth (int n) const {
    const NodeType *node = &begin_;
    while (n--) node = node->next;
    return node->next->value;
  }
  void forEach (const std::function<void (const ValueType &)> &callback) {
    NodeType *node = &begin_;
    while (node->next != &end_) {
      callback(node->next->value);
      node = node->next;
    }
  }
};

class NoMoreItems : public std::exception {};

template <typename T>
class Stream {
 protected:
  template <typename U>
  friend class Stream;

  List<T> elements;
  virtual T next (int) = 0;
 public:
  virtual ~Stream () {}
  T get (int n) {
    while (elements.size() <= n) elements.push_back(this->next(elements.size()));
    return elements.nth(n);
  }
  T operator[] (int n) { return get(n); }
  operator std::vector<T> () {
    std::vector<T> result;
    try {
      for (int i = 0;; ++i) result.push_back(get(i));
    } catch (const NoMoreItems &) {}
    return result;
  }

  virtual std::string getType () const = 0;
};

class RangeStream : public Stream<int> {
 private:
  int l, r, step;
 protected:
  int next (int i) {
    int res = l + i * step;
    if (res >= r) throw NoMoreItems();
    return res;
  }
 public:
  RangeStream (int l, int r, int step = 1) : l(l), r(r), step(step) {}
  RangeStream (int r) : RangeStream(0, r) {}
  std::string getType () const { return "range"; }

  friend int getStep (const Stream<int> *stream);
};

int getStep (const Stream<int> *stream) {
  if (stream->getType() != "range") throw std::exception();
  return dynamic_cast<const RangeStream *>(stream)->step;
}

class StringStream : public Stream<char **> {
 private:
  int maxn = -1;
  const std::string str;
 protected:
  char **next (int len) {
    if (maxn > 0 && len >= maxn) throw NoMoreItems();
    char **array = new char *[str.length()];
    for (int i = 0; i < str.length(); ++i) {
      array[i] = new char[len + 2];
      for (int j = 0; j <= len; ++j) array[i][j] = str[i];
      array[i][len + 1] = '\0';
    }
    return array;
  }
 public:
  StringStream (std::string str) : str(str) {}
  StringStream (std::string str, int maxn) : str(str), maxn(maxn) {}
  StringStream (const StringStream &other) = delete;
  std::string getType () const { return "string"; }
  bool operator< (const StringStream &that) const {
    return str < that.str;
  }
  ~StringStream () {
    Stream<char **>::elements.forEach([this] (char ** const &array) {
      for (int i = 0; i < str.length(); ++i) delete[] array[i];
      delete[] array;
    });
  }
};

template <typename T, typename U>
class MappedStream : public Stream<T> {
 private:
  T (*mapping)(const U &);
  Stream<U> *base;
 protected:
  T next (int i) { return mapping(base->get(i)); }
 public:
  MappedStream (T (*mapping)(const U &), Stream<U> *base) : mapping(mapping), base(base) {}
  std::string getType () const { return "mapped"; }
};

class IntegerStream : public Stream<int> {
 protected:
  int next (int i) { return i; }
 public:
  IntegerStream () = default;
  static IntegerStream stream;
  static int getNth (int n) {
    return stream.get(n);
  }
  std::string getType () const { return "integer"; }
};

IntegerStream IntegerStream::stream;

// --------------------------------------------------------------------------
// | 以下的部分不需要做出改动，除非你用了 std::list（见对应注释），仅供参考 |
// --------------------------------------------------------------------------

// 把输入的 base 流 a_n 变换成 S_n=a_1+...+a_n
template <typename T>
class SumStream : public Stream<T> {
 private:
  Stream<T> *base;
 protected:
  T next (int i) {
    if (i == 0) return base->get(i);
    return this->get(i - 1) + base->get(i);
  }
 public:
  SumStream (Stream<T> *base) : base(base) {}
  std::string getType () const { return "sum"; }
};

template <typename T>
class EulerTransform : public Stream<T> {
 private:
  Stream<T> *base;
 protected:
  // b_n=a_{n+2}-\frac{(a_{n+2}-a_{n+1})^2}{a_n-2a_{n+1}+a_{n+2}}
  // 如果 Leibniz 级数 \lim_{n\to+\infty}a_n=a, 则 \lim_{n\to+\infty} 存在且也为 a，而且 b_n 比 a_n 收敛地更快
  T next (int i) {
    T a0 = base->get(i), a1 = base->get(i + 1), a2 = base->get(i + 2);
    return a2 - ((a2 - a1) * (a2 - a1) / (a0 - 2 * a1 + a2));
  }
 public:
  EulerTransform (Stream<T> *base) : base(base) {}
  std::string getType () const { return "euler"; }
};

template <typename T>
class QuickStream : public Stream<T> {
 private:
  class StreamStream : public Stream<Stream<T> *> {
   private:
    Stream<T> *base;
   protected:
    Stream<T> *next (int i) {
      if (i == 0) return base;
      return new EulerTransform<T>(this->get(i - 1));
    }
   public:
    StreamStream (Stream<T> *base) : base(base) {}
    StreamStream (const StreamStream &) = delete;
    ~StreamStream () {
      // ------------------------------------------------------------
      // | 如果你用了 std::list，你需要把下面这行替换成注释里的那行 |
      // ------------------------------------------------------------
      Stream<Stream<T> *>::elements.forEach([this] (Stream<T> * const &x) { if (x != base) delete x; });
      // for (const auto &x : Stream<Stream<T> *>::elements) if (x != base) delete x;
      // ↑替换成这行
    }
    std::string getType () const { return "table"; }
  };
  static T streamFirst (Stream<T> * const &stream) { return stream->get(0); }
  StreamStream streams;
  MappedStream<T, Stream<T> *> mapped;
 protected:
  T next (int i) { return mapped.get(i); }
 public:
  QuickStream (Stream<T> *base) : streams(base), mapped(MappedStream<T, Stream<T> *>(streamFirst, &streams)) {}
  std::string getType () const { return "quick"; }
};

double piElement (const int &i) {
  return (i % 2 == 0 ? 1 : -1) / static_cast<double>(2 * i + 1);
}

double times4 (const double &d) { return d * 4; }

int main () {
  // range stream tests
  Stream<int> *r = new RangeStream(4);
  std::vector<int> vec = *r;
  for (const int &i : vec) cout << i << ' ';
  cout << endl;
  delete r;

  r = new RangeStream(2, 4);
  vec = *r;
  for (const int &i : vec) cout << i << ' ';
  cout << endl;
  delete r;

  r = new RangeStream(1, 9, 2);
  vec = *r;
  for (const int &i : vec) cout << i << ' ';
  cout << endl;
  cout << getStep(r) << endl;
  try {
    getStep(&IntegerStream::stream);
  } catch (...) {
    cout << "Good" << endl;
  }
  delete r;

  // string stream tests
  Stream<char **> *strstream = new StringStream("Hello");
  cout << (*dynamic_cast<StringStream *>(strstream) < StringStream("World")) << endl;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) cout << (*strstream)[i][j] << ' ';
    cout << endl;
  }
  cout << endl;
  delete strstream;
  strstream = new StringStream("World", 5);
  std::vector<char **> vecs = *strstream;
  for (char **array : vecs) {
    for (int i = 0; i < 5; ++i) cout << array[i] << ' ';
    cout << endl;
  }
  vecs = *strstream;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) cout << (*strstream)[i][j] << ' ';
    cout << endl;
  }
  cout << endl;
  delete strstream;

  // integer stream tests
  for (int i = 0; i < 10; ++i) cout << IntegerStream::stream[i] << ' ';
  cout << endl;
  for (int i = 0; i < 10; ++i) cout << IntegerStream::getNth(i) << ' ';
  cout << endl;

  // pi stream tests
  Stream<double> *piElementStream = new MappedStream<double, int>(piElement, &IntegerStream::stream);
  Stream<double> *piStream4 = new SumStream<double>(piElementStream);
  Stream<double> *piStream = new MappedStream<double, double>(times4, piStream4);
  Stream<double> *quickPi = new EulerTransform<double>(piStream);
  Stream<double> *reallyQuickPi = new QuickStream<double>(piStream);
  cout.precision(18);
  for (const auto &x : { piStream, quickPi, reallyQuickPi }) {
    for (int i = 0; i < 10; ++i) {
      cout << x->get(i) << endl;
      if (x->get(i) != (*x)[i]) throw std::exception();
    }
    cout << endl;
  }
  for (const auto &x : { piElementStream, piStream, piStream4, quickPi, reallyQuickPi }) delete x;
  return 0;
}
