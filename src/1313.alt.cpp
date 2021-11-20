#include <bits/stdc++.h>


#include <string>
#include <set>

struct Wrapper {
  void (*func)(std::string);
  void (*before)();
  void (*after)();
};

std::set<size_t> wrappers;

Wrapper *create (void (*func)(std::string), void (*before)(), void (*after)()) {
  Wrapper *wrapper = new Wrapper;
  wrapper->func = func;
  wrapper->before = before;
  wrapper->after = after;
  wrappers.insert(reinterpret_cast<size_t>(wrapper));
  return wrapper;
}

void remove (const Wrapper *wrapper) {
  wrappers.erase(reinterpret_cast<size_t>(wrapper));
  delete wrapper;
}

void run (const Wrapper *wrapper, const std::string &arg) {
  wrapper->before();
  wrapper->func(arg);
  wrapper->after();
}

void destroy () {
  for (const auto &ptr : wrappers) delete reinterpret_cast<Wrapper *>(ptr);
  wrappers.clear();
}

using namespace std;

void foo (string id) { cout << id << endl; }
void before () { cout << "before foo" << endl; }
void after () { cout << "after foo" << endl; }

int main (){
    Wrapper *f = create(foo, before, after);
    run(f, "Hello");
    Wrapper *g = create(foo, after, before);
    run(g, "World!");
    remove(g);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    remove(g);
    g = create(foo, after, before);
    remove(g);
    g = create(foo, after, before);
    remove(g);
    g = create(foo, after, before);
    remove(g);
    g = create(foo, after, before);
    remove(g);
    g = create(foo, after, before);
    remove(g);
    g = create(foo, after, before);
    remove(g);

    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    g = create(foo, after, before);
    destroy();
    return 0;
}
