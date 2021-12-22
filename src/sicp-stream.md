<div data-theme-toc="true"> </div>

## 前言

为了帮助大家复习程设考试中的各种 C++ 语法，我出了这道题，应该覆盖了所有强调过的机考考点，大家可以视自己情况过一下。难度和工程量预期为稍高于一般的小作业题，低于 Pokedex 和 ACM Express 等题。链表可以直接用 [1363. Linklist Without Name][1363] 测，其余部分过了样例应该就差不多了。

[1363]: https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1363

# SICP Stream

## 题目背景

（这一段可以直接跳过。）

<small>panic 一直想给大家安利 [Structure and Interpretation of Computer Programs (aka SICP)](https://mitpress.mit.edu/sites/default/files/sicp/index.html) 这本书，但是这本书里用的语言是 Scheme（一种 Lisp 方言），对于大多数 C++ 使用者并不友好。刚好前段时间大家在实现 PyList，于是他在试图整合期末考点的时候想到了可以实现一些 SICP 里的东西。</small>

<small>我对它印象最深刻的章节之一就是这一段，它非常优美地实现了 π 的计算，以及其他很多神奇的事情。并且，它是 SICP 前半段里少有的没有大面积出现递归、lambda、car、cdr 等等的章节，很适合让同学们实现。于是——</small>

<small>题目改编自 SICP 3.5.3 一节。</small>

## 题目描述

在本题里，你需要实现一个：

- 链表（如果你觉得自己链表写的已经很熟练了，可以直接用 `std::list`）
- 流
- 类似 Python 的 `range`
- 简单的流处理

具体来说，你需要实现这些类：

- `List<T>`
- `Stream<T>`（预期代码量：30 行左右，这个数字包含了已给出的代码和需要你自己实现的代码，下同）
- `RangeStream : public Stream<int>`（预期代码量：35 行左右）
- `StringStream : public Stream<char **>`（预期代码量：30 行左右）
- `MappedStream<T, U> : public Stream<T>`（预期代码量：15 行左右）
- `IntegerStream : public Stream<int>`（预期代码量：15 行左右）

看着比较多，但是除了链表之外，实际需要自己填充的只有 50 多行，大部分代码都已经给出了。

你应该以模板代码作为一个 starting point，并且需要保证没有内存泄漏（可以用 Valgrind 检查）。

作为题目设计的目标，这个题目应该覆盖了所有强调过的考点。如果你发现有一个考点强调过，却没有在这个题目里出现，请立即联系 @panic。

### List 类

如果你觉得自己链表写的已经很熟练了，可以不写链表，直接用 `std::list`。

（下面有完整的模板代码，如果需要复制请直接从那里复制。）

```cpp
// 你可以直接把 1363. Linklist Without Name 的代码搬过来
template <typename ValueType>
class List {
 public:
  List (); // TODO
  List (List &&obj); // TODO
  List (const List &foreign); // TODO
  ~List (); // TODO

  // 这两个函数是 std::list 和 1363 都没有的
  // 返回第 n 个元素, 0-based
  const ValueType &nth (int n) const; // TODO
  // 对于每个元素调用一次 callback
  void forEach (const std::function<void (const ValueType &)> &callback); // TODO

  void push_back (const ValueType &value); // TODO
  int size () const; // TODO

  // 下面这些函数与其余部分代码无关，删掉也能正常跑，仅供练习链表使用
  void pop_back (); // TODO
  void push_front (const ValueType &value); // TODO
  void pop_front (); // TODO
  ValueType &front () const; // TODO
  ValueType &back () const; // TODO
  void insert (int index, const ValueType &value); // TODO
  void erase (int index); // TODO
  void clear (); // TODO
};
```

### Stream 类

Stream 类表示一个以 `T` 为类型的「流」，就是一个 `T` 为类型的序列；例如，如果 `T` 是实数，那么 `Stream<T>` 就是实数列。这个流可能有有限长，也可能有无限长。

要做到支持无限长的流，我们不能在流初始化的时候就生成其中所有的元素，而是应该随用随生成。生成过的元素应该保存在一个链表里，下次被使用的时候**不会**再次调用生成函数。（换句话说，对于每个 `int n`，`next(n)` 至多会被调用一次。）

`next(int n)` 的功能是返回第 `n` 个元素的值（0-based）。由于 Stream 是一个抽象的类，这个函数应该是一个纯虚函数。

`get` 函数和 `[]` 运算的功能一致，都是取出这个流里的第 `n` 个元素（0-based）。在实现的时候，应该先检查 `elements` 里是不是已经存在了，如果已经有了就直接返回；如果没有就依次调用 `next(m), next(m+1), ..., next(n-1), next(n)` 生成第 `m, m+1, ..., n` 个元素并存储到 `elements` 里，其中 `m` 是缺少的第一个元素的 index。

为了练习 vector 的使用，你还需要写一个 `operator vector` 把一个有限的 Stream 转换成 Vector。试图将无限的 Stream 转为 Vector 是未定义行为。注意，转换的时候不光需要返回链表里的内容，还需要生成**所有未生成的元素**，直到没有后续元素为止。例如，`vector<int>(RangeStream(5))` （`RangeStream` 的含义见下）应该是 0, 1, 2, 3, 4 而非一个空 vector。你仍然需要保证在整个生命周期里 `next(n)` 对于每个 `n` 至多只被调用一次。

（如果你对 C++ 的 `istream`/`ostream` 比较熟悉：这个 Stream 和 `istream`/`ostream` 里的 stream 完全不是一个东西！请勿混淆。）

```cpp
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
  T get (int n); // TODO
  // TODO: operator[]
  operator std::vector<T> (); // TODO

  // TODO: 纯虚函数 std::string getType () const; 可以参考下面对 getType 的实现。
  // TODO: 添加其他你认为需要的函数
};
```

### RangeStream 类

`RangeStream(l, r, step)` 会返回 l, l+step, l+2step, ... 这个序列，直到元素即将大于等于 r 为止，换句话说，返回的元素一定在 $[l,r)$ 之间。例如，`RangeStream(2, 13, 3)` 里的内容应该是 2, 5, 8, 11。`RangeStream(max)` 则会返回 0, 1, 2, ..., max-1。

为了练习 `dynamic_cast` 的使用（~~其实是因为实在想不到其他的方式用 dynamic_cast 了~~），你还需要实现一个 getStep 函数，这个函数输入一个 `Stream<int> *`，并检查它是不是 `RangeStream`；如果不是则抛出异常，如果是则返回这个 `RangeStream` 的 `step` 参数。

（如果你用过 Python，这个类类似于 Python 中的 `range` 函数。）

```cpp
class RangeStream : public Stream<int> {
 private:
  // 你不能将 step 设为 public，而是应该利用 friend 来使 getStep 能读到 step
  // TODO: friend 函数 getStep 声明
  int l, r, step;
 protected:
  // 在 i 超限的时候 throw 出一个 NoMoreItems 对象
  int next (int i); // TODO
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
```

### StringStream 类

这个流是一个「复读机」流，对于输入的 string 里的每个字符进行复读，复读的次数不断增加，返回一个字符串数组。

比如说 `StringStream("Hello")` 的第 0, 1, 2 项依次应为：

```plain
{"H", "e", "l", "l", "o"},           // [0]
{"HH", "ee", "ll", "ll", "oo"},      // [1]
{"HHH", "eee", "lll", "lll", "ooo"}, // [2]
```

注意第 `i` 个元素（0-based）里，应该复读 `i+1` 遍。

为了练习运算符重载的使用，你还需要实现一个 `operator<`，排序为 `str` 的字典序。例如，`StringStream("Hello") < StringStream("World")` 为 `true`。

当然，复读机有可能不能无限复读；`StringStream` 支持传入第二个参数 `maxn`，表示最多复读 `maxn` 遍。例如 `StringStream("Hello", 3)` 里应该只有上面示例里的三个元素。当 `maxn` < 0 时表示无限制。

```cpp
class StringStream : public Stream<char **> {
 private:
  int maxn = -1;
  const std::string str;
  // 不要添加其他的成员变量
 protected:
  char **next (int len); // TODO
 public:
  StringStream (std::string str) : str(str) {}
  StringStream (std::string str, int maxn) : maxn(maxn), str(str) {}
  StringStream (const StringStream &other) = delete;
  std::string getType () const { return "string"; }
  // TODO: operator<
  // TODO: 添加其他你认为需要的函数
};
```

### MappedStream 类

这个类是一个流转换器。它输入一个函数 `mapping` $: U\to T$ 和另一个流 `Stream<U> *base`。例如我们有一个函数：

```cpp
double mapping (const int &i) {
  return 1 / ((double) i + 1);
}
```

把 `RangeStream(5)` （即 0, 1, 2, 3, 4）通过这个函数之后，它会变成 1.0, 0.5, 0.333..., 0.25, 0.2。

需要支持的用法：

```cpp
double piElement (const int &i) { // const U &
  return (i % 2 == 0 ? 1 : -1) / static_cast<double>(2 * i + 1);
}

Stream<int> *rs = new RangeStream(19260817);
Stream<double> *piElementStream = new MappedStream<double, int>(piElement, rs);
```

模板：

```cpp
template <typename T, typename U>
class MappedStream : public Stream<T> {
 private:
  // TODO: 怎么写 mapping 的声明？（提示：可以用 std::function，但是建议练练手写函数指针声明。）
  Stream<U> *base;
 protected:
  T next (int i) { return mapping(base->get(i)); }
 public:
  // TODO: 构造函数 MappedStream (类型声明应该怎么写？ mapping, Stream<U> *base);
  std::string getType () const { return "mapped"; }
  // TODO: 添加其他你认为需要的函数
};
```

### IntegerStream 类

这个类是一个无限流，内容为 0, 1, 2, 3, ...。

大部分代码已经给出，只需要补充实现一个 static 成员变量 `static IntegerStream stream` 和一个 static 函数 `getNth(int)`。用法示例：

```cpp
int main () {
  for (int i = 0; i < 10; ++i) cout << IntegerStream::stream[i] << ' '; // 0 1 2 3 4 5 6 7 8 9
  cout << endl;
  for (int i = 0; i < 10; ++i) cout << IntegerStream::getNth(i) << ' '; // 0 1 2 3 4 5 6 7 8 9
  cout << endl;
}
```

模板：

```cpp
class IntegerStream : public Stream<int> {
 protected:
  int next (int i) { return i; }
 public:
  IntegerStream () = default;
  // TODO: stream
  // TODO: getNth
  std::string getType () const { return "integer"; }
};
```

### 后续

（这一段可以直接跳过。）

<small>在题目背景中我提到，用这种流式处理可以计算 π。它靠的是一个叫 Euler Transform 的方法，这个定理叫做，对于一个收敛的 Leibniz 级数 $a_n$ ，可以构造出一个 Leibniz 级数 $b_n$ 使得两者收敛于同一值，且 $b_n$ 比 $a_n$ 收敛地更快。这个公式是 $S_n'=S_{n+2}-\frac{(S_{n+2}-S_{n+1})^2}{S_n-2S_{n+1}+S_{n+2}}$ ，其中 $S_n$ 是 $a_n$ 的部分和， $S_n'$ 是 $b_n$ 的部分和。</small>

<small>于是结合 $\frac\pi4=1-\frac13+\frac15-\frac17+\cdots$ ，只需要构造出这个趋近于 π 的数列然后不停地应用 Euler Transform，就可以方便快捷地计算出 π。</small>

<small>代码已在下方给出，如果你有兴趣可以读读。</small>

### 完整模板代码

这份代码在填充完成之后可以直接独立编译运行。换句话说，这是一个 cpp 文件，而不是 hpp 文件。

```cpp
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
// 如果你不想手写 std::list:
// #include <list>

using std::cin;
using std::cout;
using std::endl;

// 你可以直接把 1363. Linklist Without Name 的代码搬过来
template <typename ValueType>
class List {
 public:
  List (); // TODO
  List (List &&obj); // TODO
  List (const List &foreign); // TODO
  ~List (); // TODO

  // 这两个函数是 std::list 和 1363 都没有的
  // 返回第 n 个元素, 0-based
  const ValueType &nth (int n) const; // TODO
  // 对于每个元素调用一次 callback
  void forEach (const std::function<void (const ValueType &)> &callback); // TODO

  void push_back (const ValueType &value); // TODO
  int size () const; // TODO

  // 下面这些函数与其余部分代码无关，删掉也能正常跑，仅供练习链表使用
  void pop_back (); // TODO
  void push_front (const ValueType &value); // TODO
  void pop_front (); // TODO
  ValueType &front () const; // TODO
  ValueType &back () const; // TODO
  void insert (int index, const ValueType &value); // TODO
  void erase (int index); // TODO
  void clear (); // TODO
};

// 用来在 next() 没有下一个元素的时候 throw 出来
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
  T get (int n); // TODO
  // TODO: operator[]
  operator std::vector<T> ();

  // TODO: 纯虚函数 std::string getType () const; 可以参考下面对 getType 的实现。
  // TODO: 添加其他你认为需要的函数
};

class RangeStream : public Stream<int> {
 private:
  int l, r, step;
 protected:
  // 在 i 超限的时候 throw 出一个 NoMoreItems 对象
  // TODO: friend 函数 getStep 声明
  int next (int i); // TODO
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
  int maxn = -1;
  const std::string str;
  // 不要添加其他的成员变量
 protected:
  char **next (int len); // TODO
 public:
  StringStream (std::string str) : str(str) {}
  StringStream (std::string str, int maxn) : maxn(maxn), str(str) {}
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
  // TODO: 构造函数 MappedStream (类型声明应该怎么写？ mapping, Stream<U> *base);
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
  // S_n'=S_{n+2}-\frac{(S_{n+2}-S_{n+1})^2}{S_n-2S_{n+1}+S_{n+2}}
  // 如果 Leibniz 级数 a_n 部分和为 \lim_{n\to+\infty}S_n=a, 则 \lim_{n\to+\infty}S_n' 存在且也为 a，而且 S_n' 比 S_n 收敛地更快
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
```

## 样例输入

无

## 样例输出

```plain
0 1 2 3
2 3
1 3 5 7
2
Good
1
H e l l o
HH ee ll ll oo
HHH eee lll lll ooo
HHHH eeee llll llll oooo
HHHHH eeeee lllll lllll ooooo

W o r l d
WW oo rr ll dd
WWW ooo rrr lll ddd
WWWW oooo rrrr llll dddd
WWWWW ooooo rrrrr lllll ddddd
W o r l d
WW oo rr ll dd
WWW ooo rrr lll ddd
WWWW oooo rrrr llll dddd
WWWWW ooooo rrrrr lllll ddddd

0 1 2 3 4 5 6 7 8 9
0 1 2 3 4 5 6 7 8 9
4
2.66666666666666696
3.46666666666666679
2.89523809523809561
3.33968253968254025
2.97604617604617649
3.28373848373848443
3.01707181707181782
3.25236593471887669
3.04183961892940324

3.16666666666666696
3.13333333333333375
3.14523809523809561
3.13968253968254007
3.14271284271284346
3.14088134088134163
3.14207181707181782
3.14125482360776553
3.14183961892940333
3.1414067184965031

4
3.16666666666666696
3.14210526315789496
3.14159935731900486
3.14159271403377849
3.14159265397529275
3.14159265359117645
3.14159265358977802
3.14159265358979534
3.14159265358979489
```
