#include <iostream>
#include <set>

using std::cin, std::cout, std::endl;

typedef unsigned long long num_t;

num_t factorial (num_t n) {
  if (n == 0) return 1;
  num_t res = n;
  while (--n) res *= n;
  return res;
}

num_t encode (const num_t *numbers, num_t length) {
  num_t res = 1;
  std::set<num_t> numbersUnused;
  for (num_t i = 0; i < length; ++i) numbersUnused.insert(i + 1);
  for (num_t i = 0; i < length; ++i) {
    num_t number = numbers[i];
    numbersUnused.erase(number);
    num_t fac = factorial(length - i - 1);
    std::set<num_t> numbersUsable = numbersUnused;
    const auto firstToRemove = numbersUsable.upper_bound(number);
    if (firstToRemove != numbersUsable.end()) {
      numbersUsable.erase(firstToRemove, numbersUsable.end());
    }
    res += fac * numbersUsable.size();
  }
  return res;
}
void decode (num_t number, num_t length, num_t *store) {
  num_t current = number - 1;
  std::set<num_t> numbersUnused;
  for (num_t i = 0; i < length; ++i) numbersUnused.insert(i + 1);
  for (num_t i = 0; i < length; ++i) {
    num_t fac = factorial(length - i - 1);
    num_t div = current / fac;
    auto it = numbersUnused.begin();
    std::advance(it, div);
    num_t number = *it;
    store[i] = number;
    numbersUnused.erase(number);
    current %= fac;
  }
}

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  num_t length, delta;
  cin >> length >> delta;
  num_t input[length];
  for (num_t i = 0; i < length; ++i) cin >> input[i];
  num_t output[length];
  decode(encode(input, length) + delta, length, output);
  for (num_t i = 0; i < length; ++i) cout << output[i] << ' ';
  cout << endl;
  return 0;
}
