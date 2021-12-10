#include <functional>
#include <vector>

class Defer {
 private:
  std::vector<std::function<void (void)>> fs;
 public:
  Defer () = delete;
  template <typename Functor>
  Defer (Functor f) : fs({f}) {}
  template <typename Functor>
  void operator() (Functor f) { fs.push_back(f); }
  ~Defer () {
    while (!fs.empty()) {
      fs.back()();
      fs.pop_back();
    }
  }
};
