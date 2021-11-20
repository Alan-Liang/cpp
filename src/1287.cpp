#include <unordered_map>

// class BigIndexArray {
//  private:
//   using T = long long;
//   std::unordered_map<T, T> array;
//  public:
//   T &operator[] (T ix) {
//     return array[ix];
//   }
// };

using BigIndexArray = std::unordered_map<long long, long long>;

#include <iostream>

using namespace std;

int main(){
  BigIndexArray a;
  a[-922337203685477580] = 9223372036854775807;
  cout << a[-922337203685477580] << endl;
}
