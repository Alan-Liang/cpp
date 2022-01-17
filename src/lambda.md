因为 lambda 表达式是今年新增的考查内容, 没有往年真题, 所以我胡乱编了一些题来帮助大家复习. 这些题目应当是复习之后的检验, 而非复习前的索引; 你应当复习完成之后再来看这些东西.

感谢验题人: @yixindong, @0dot3, @lauyeeyu 指出了最初的题面里的一大堆问题. 由于这部分我也不是完全熟悉, 现在这个版本可能还会有各种各样奇怪的问题, 也有可能有没覆盖到的点, 欢迎在下面发帖反馈.

由于笔试的时候不能携带任何电子设备, 你应当能在不借助编译器或 IDE 的情况下完成这些题目. 由于后面的题目有对前面题目提示, 建议你顺序完成题目, 在完成前一题之前暂时不要看后面的题干. 所有题目均仅限 C++11, 不考虑全局变量 (包括 static 变量和全局 constexpr), 不考虑 C++14 及之后的扩展, 不考虑 `#define` 等奇怪因素的影响.

**一、不定项选择题**

**Q1.** 以下关于 lambda 函数的说法中错误的是/有:
A. 也称 lambda 表达式
B. 可以定义在函数的内部
C. 可以使用前置返回类型
D. 可以嵌套定义
[wrap=placeholder key="Q1" description="请输入你的答案" default=""][/wrap]

**Q2.** lambda 函数的结构中有哪些部分?
A. 返回类型
B. 函数名
C. 参数表
D. 捕获列表
E. 函数体
[wrap=placeholder key="Q2" description="请输入你的答案" default=""][/wrap]

**Q3.** lambda 函数的结构中, 可以省略的有哪个/哪些? (前后的括号也算进对应的结构里)
A. 返回类型
B. 参数表
C. 捕获列表
D. 函数体
[wrap=placeholder key="Q3" description="请输入你的答案" default=""][/wrap]

**Q4.** 下列哪个/哪些 lambda 函数一定是**不**合法的? (为什么?)
A. `[] {}`
B. `() -> int { return 0; }`
C. `[] -> int { return 0; }`
D. `[] () -> void { return 0; }`
E. `[] (const std::string &) { return 0; }`
F. `[] { return a; }`
G. `[this] { return a; }`
[wrap=placeholder key="Q4" description="请输入你的答案" default=""][/wrap]

<details>
<summary>参考答案</summary>

C ACDE AB BCDF
你的答案 (抱歉, 这里没有自动评分):
=Q1= =Q2= =Q3= =Q4=

解释:
Q1. 1-9 章 PPT P448
Q2. lambda 是匿名函数, 没有函数名
Q3. 1-9 章 PPT P450
Q4.
B: 捕获列表不能省略
C: 不省略返回类型时, 参数列表也不能省略
D: 声明的返回值类型为 `void`, 实际返回了个 `int`
F: 没有捕获 `a` 就用了 `a`

***

</details>

**二、代码题**

**Q5.** 请用 lambda 表达式重写这个函数:

```cpp
int succ (int x) {
  return x + 1;
}
```

[wrap=placeholder key="Q5" description="请输入你的答案" default="... succ = ...;"][/wrap]

<details>
<summary>参考答案</summary>

答案不唯一, 例如, 以下每一行均为正确答案:

```cpp
auto succ = [] (int x) { return x + 1; };
auto succ = [] (int x) -> int { return x + 1; };
auto succ = [&] (int x) { return x + 1; };
auto succ = [=] (int x) { return x + 1; };

// 你的答案:
=Q5=
```

***

</details>

**Q6.** 假设你有一个这样的 main 函数:

```cpp
int main () {
  int count = 0;
  std::set<int> set;
  int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, ...;
  auto func = [???] () {};
}
```

请写出一个捕获列表 (即补全 `???`), 使得 `func` 能访问到 `main` 里的所有变量, 且满足以下条件:
- 按值访问 `count`
- 按引用访问 `set`
- 按值访问其他所有变量

[wrap=placeholder key="Q6" description="请输入你的答案" default=""][/wrap]

<details>
<summary>参考答案</summary>

```cpp
// 正确答案:
auto func = [=, &set] () {};

// 一些典型错误答案:
auto func = [=] () {};
auto func = [&set, =] () {}; // = 或者 & 必须在第一个; 翁阿姨 ppt 上的是错的 (已确认过)
auto func = [=, count, &set] () {}; // 已声明默认按值访问, 不能重复定义
auto func = [&, set] () {}; // 搞反了
```

***

</details>

**Q7-Q11.** 以下每个代码段里的 lambda 表达式都有一处问题, 这个问题会导致编译期报错或运行时表现不正常, 请指出这处问题是什么, 并予以修正.

**Q7.**

```cpp
int i = 0, j = 1, k = 2;
auto f = [i, &] () -> int { return i; };
```

<details>
<summary>参考答案</summary>

在写捕获列表的时候默认捕获需要写在第一个:
```cpp
int i = 0, j = 1, k = 2;
auto f = [&, i] () -> int { return i; };
```

***

</details>

**Q8.**

```cpp
auto resultOrInvalid = [] (bool err, std::string result) {
  if (err) return "Invalid";
  return result;
};
resultOrInvalid(true, "Meaningless Gibberish"); // "Invalid"
resultOrInvalid(false, "Meaningful Result"); // "Meaningful Result"
```

<details>
<summary>参考答案</summary>

`"Invalid"` 的类型为 `const char[8]`, 因此类型推断认为这个函数返回的是 `const char *` 而非 `std::string`. 改法可以有 (至少) 三种, 一是手动声明返回类型:

```cpp
auto resultOrInvalid = [] (bool err, std::string result) -> std::string {
  if (err) return "Invalid";
  return result;
};
```

第二种是把 `const char *` 转换成 `std::string` 再返回:

```cpp
auto resultOrInvalid = [] (bool err, std::string result) {
  if (err) return std::string("Invalid");
  return result;
};
```

第三种是直接用三目运算符 `?:`, 它会自动做类型转换: (courtesy of @qweryy0566)

```cpp
auto resultOrInvalid = [] (bool err, std::string result) {
  return err ? "Invalid" : result;
};
```

提醒: 不同的 lambda 有可能属于不同类型, 所以不能这样写:

```cpp
auto f = [] (bool cond) {
  if (cond) return [] {};
  return [] {};
};
```

而是需要:

```cpp
auto f = [] (bool cond) -> std::function<void (void)> {
  if (cond) return [] {};
  return [] {};
};
```

***

</details>

**Q9.**

```cpp
int main () {
  int count = 0;
  auto next = [] () -> int { return count++; };
  next(); // 0
  next(); // 1
  next(); // 2
}
```

<details>
<summary>参考答案</summary>

没有捕获 count.

```cpp
int main () {
  int count = 0;
  auto next = [&count] () -> int { return count++; };
  next(); // 0
  next(); // 1
  next(); // 2
}
```

***

</details>

**Q10.** (本题的修改方法较为奇怪, 所以如果想不到也没关系, 只要找出错误点即可)

```cpp
auto getCounter () {
  int count = 0;
  return [&] () -> int { return count++; };
}

int main () {
  auto counter = getCounter();
  auto counter2 = getCounter();
  counter(); // 0
  counter2(); // 0
  counter(); // 1
  counter(); // 2
  counter2(); // 1
}
```

<details>
<summary>参考答案</summary>

标准的错误修改 (courtesy of @yixindong and @lauyeeyu):

```cpp
auto getCounter () {
  static int count = 0;
  return [&] () -> int { return count++; };
}
```

如果你写出了这个答案, 可以再想一想.

`count` 是 `getCounter` 里的变量, 存储在 `getCounter` 的栈空间里, 一旦函数返回了，栈空间里的变量就会失效, 所以捕获的引用就失效了.

此题修改方法较为复杂, 这里不能按值访问, 因为按值访问的时候是无法修改值的. 一种方法是构造一个 `shared_ptr<int>`:

```cpp
auto getCounter () {
  auto count = std::make_shared<int>();
  return [=] () -> int { return (*count)++; };
}
```

还有一种方法是用一个 `static` 的 `vector<int>` (但是这种方法会导致实质上的内存泄漏):

```cpp
auto getCounter () {
  static std::vector<int> counts;
  int id = counts.size();
  counts.push_back(0);
  return [=] () -> int {
    return counts[id]++;
  };
}
```

***

</details>

**Q11.** 感谢 @guojunxian 提醒我这个问题.

```cpp
#include <iostream>

void execute (void (*func)(void)) {
  func();
}

int main () {
  int a;
  std::cin >> a;
  execute([&] { std::cout << a << std::endl; });
}
```

<details>
<summary>参考答案</summary>

只有不带捕获的 lambda 函数才能转换为函数指针. (想想为什么?) 修改方法之一是用 `std::function` 代替函数指针:

```cpp
void execute (std::function<void (void)> func) {
  func();
}
```

</details>
