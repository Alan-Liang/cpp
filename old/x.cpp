class Class {};
struct Struct {};
typedef int Typename;
namespace Namespace {};
void Function () {}
int Variable;

class Foo {
 public:
  void bar () {}
};

int main () {
  auto     class_ = &Class;
  auto    struct_ = &Struct;
  auto  typename_ = &Typename;
  auto namespace_ = &Namespace;
  auto  function_ = &Function;
  auto    method_ = &Foo::bar;
  auto  variable_ = &Variable;
}
