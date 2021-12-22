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
class List {
 public:
  List ();
  List (List &&obj);
  List (const List &foreign);
  ~List ();

  // 这两个函数是 std::list 和 1363 都没有的
  // 返回第 n 个元素, 0-based
  const ValueType &nth (int n) const;
  // 对于每个元素调用一次 callback
  void forEach (const std::function<void (const ValueType &)> &callback);

  void push_back (const ValueType &value);
  int size () const;

  // 下面这些函数与其余部分代码无关，删掉也能正常跑，仅供练习链表使用
  void pop_back ();
  void push_front (const ValueType &value);
  void pop_front ();
  ValueType &front () const;
  ValueType &back () const;
  void insert (int index, const ValueType &value);
  void erase (int index);
  void clear ();
};

class NoMoreItems : public std::exception {};

template <typename T>
class Stream {
 protected:
  // TODO: friend 的声明
  // 你需要把所有 Stream<U> 都声明为 Stream 的 friend，不管 T 和 U 是不是一个东西

  // 如果你想用 std::list，把下面这行替换成
  // std::list<T> elements;
  List<T> elements;
  // TODO: 纯虚函数 T next (int);
 public:
  T get (int n);
  // TODO: operator[]
  operator std::vector<T> ();

  // TODO: 纯虚函数 std::string getType () const; 可以参考下面对 getType 的实现。
  // TODO: 添加其他你认为需要的函数
};

class RangeStream : public Stream<int> {
 private:
  int l, r, step;
 protected:
  // 在 i 超限的时候 throw 出一个 NoMoreItems
  // TODO: friend 函数 getStep 声明
  int next (int i);
 public:
  RangeStream (int l, int r, int step = 1) : l(l), r(r), step(step) {}
  RangeStream (int r) : RangeStream(0, r) {}
  std::string getType () const { return "range"; }

  // TODO: 添加其他你认为需要的函数
};

int getStep (const Stream<int> *stream) {
  if (stream->getType() != "range") throw std::exception();
  // TODO: 返回 stream->step
}

class StringStream : public Stream<char **> {
 private:
  const std::string str;
 protected:
  char **next (int len);
 public:
  StringStream (std::string str) : str(str) {}
  StringStream (const StringStream &other) = delete;
  std::string getType () const { return "string"; }
  // TODO: operator<
  // TODO: 添加其他你认为需要的函数
};

template <typename T, typename U>
class MappedStream : public Stream<T> {
 private:
  // TODO: 怎么写 mapping 的声明？（提示：可以用 std::function，但是建议练练手写函数指针声明。）
  Stream<U> *base;
 protected:
  T next (int i) { return mapping(base->get(i)); }
 public:
  // TODO: 构造函数
  std::string getType () const { return "mapped"; }
  // TODO: 添加其他你认为需要的函数
};

class IntegerStream : public Stream<int> {
 protected:
  int next (int i) { return i; }
 public:
  IntegerStream () = default;
  // TODO: stream
  // TODO: getNth
  std::string getType () const { return "integer"; }
};

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
