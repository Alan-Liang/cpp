#include <bits/stdc++.h>


#include <string>

struct Wrapper {
  Wrapper *next = nullptr;
  void (*func)(std::string);
  void (*before)();
  void (*after)();
  static Wrapper first;
  static Wrapper *last;
};

Wrapper Wrapper::first;
Wrapper *Wrapper::last = &Wrapper::first;

Wrapper *create (void (*func)(std::string), void (*before)(), void (*after)()) {
  Wrapper *wrapper = new Wrapper;
  wrapper->func = func;
  wrapper->before = before;
  wrapper->after = after;
  Wrapper::last->next = wrapper;
  Wrapper::last = wrapper;
  return wrapper;
}

void remove (const Wrapper *wrapper) {
  Wrapper *current = &Wrapper::first;
  while (current->next != nullptr && current->next != wrapper) current = current->next;
  if (current->next == nullptr) return;
  current->next = wrapper->next;
  if (wrapper == Wrapper::last) Wrapper::last = current;
  delete wrapper;
}

void run (const Wrapper *wrapper, const std::string &arg) {
  wrapper->before();
  wrapper->func(arg);
  wrapper->after();
}

void destroy () {
  Wrapper *current = &Wrapper::first;
  while (current->next != nullptr) {
    Wrapper *aboutToDelete = current;
    current = current->next;
    if (aboutToDelete != &Wrapper::first) delete aboutToDelete;
  }
  if (current != &Wrapper::first) delete current;
  Wrapper::last = &Wrapper::first;
  Wrapper::first.next = nullptr;
}

using namespace std;

void foo (string id) { cout << id << endl; }
void before () { cout << "before foo" << endl; }
void after () { cout << "after foo" << endl; }

int main (){
    destroy();
    destroy();
    destroy();
    create(foo, before, after);
    destroy();
    destroy();
    destroy();
    destroy();
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
    destroy();
    destroy();
    return 0;
}
