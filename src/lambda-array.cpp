#include <iostream>
#include <functional>

using std::cin, std::cout, std::endl;

template <typename>
class fn;

// template <typename ReturnType, typename ...ArgTypes>
// class fn <ReturnType (ArgTypes ...)> {
//  private:
//   class CallableBase {
//    public:
//     virtual ~CallableBase () {}
//     virtual ReturnType invoke (ArgTypes ...args) = 0;
//   };
//   template <typename Functor>
//   class Callable : public CallableBase {
//    private:
//     Functor functor_;
//    public:
//     Callable (Functor functor) : functor_(functor) {}
//     ReturnType invoke (ArgTypes ...args) {
//       return functor_(args...);
//     }
//   };
//   CallableBase *callable_;
//  public:
//   template <typename Functor>
//   fn (Functor functor) {
//     callable_ = new Callable<Functor>(functor);
//   }
//   ~fn () { delete callable_; }
//   ReturnType operator() (ArgTypes ...args) {
//     return callable_->invoke(args...);
//   }
// };

template <typename ReturnType, typename ...ArgTypes>
class fn <ReturnType (ArgTypes ...)> {
 public:
  ReturnType (*function)(void *, ArgTypes...);
  void *self;
  template <typename Functor>
  fn (const Functor &functor) {
    self = reinterpret_cast<void *>(new Functor(functor));
    function = reinterpret_cast<ReturnType (*)(void *, ArgTypes...)>(&Functor::operator());
  }
  ~fn () { delete self; }
  ReturnType operator() (ArgTypes ...args) {
    return function(self, args...);
  }
};

int f (int x) { return x + 1; }

int main () {
  int j = 3, k = 4;
  fn<int (int)> arr[] = {
    [] (int a) { return a; },
    [j] (int a) { return j; },
    [&k] (int a) { return k; },
  };
  int i = 2;
  std::function<int (int)> f1 = [&i] (int a) { return i; };
  fn<int (int)> f2 = [&i] (int a) { return i; };
  // fn<int (int)> f3 = &f;
  std::cout
    << arr[0](-1) << ' '
    << arr[1](-1) << ' '
    << arr[2](-1) << ' '
    << f1(-1) << ' '
    << f2(-1) << ' '
    << f2(-1) << std::endl;
  return 0;
}
