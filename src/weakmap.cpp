#include <iostream>
#include <memory>
#include <unordered_map>

using std::cin, std::cout, std::endl;

struct Payload { int x, y, z; };
class ObservingPayload {
 public:
  std::shared_ptr<Payload> payload;
  ~ObservingPayload ();
};
std::unordered_map<Payload *, int> weakmap;
ObservingPayload::~ObservingPayload () { weakmap.erase(payload); }

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}
