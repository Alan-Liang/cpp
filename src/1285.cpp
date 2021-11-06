#include <iostream>

using std::cin, std::cout, std::endl;

struct Context {
  int *array;
  int gasRemaining;
  bool isSorted (int l, int r) {
    for (int i = l + 1; i < r; ++i) {
      if (array[i - 1] > array[i]) return false;
    }
    return true;
  }
  void mergeShuffle (int l, int r) {
    if (!gasRemaining) return;
    if (r - l < 2) return;
    gasRemaining -= 2;
    int mid = (l + r) / 2;
    mergeShuffle(l, mid);
    mergeShuffle(mid, r);
    if (isSorted(l, r)) std::swap(array[mid - 1], array[mid]);
  }
  void mergeSort (int l, int r) {
    ++gasRemaining;
    if (isSorted(l, r)) return;
    int mid = (l + r) / 2;
    mergeSort(l, mid);
    mergeSort(mid, r);
  }
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int length, count;
  cin >> length >> count;
  if (count % 2 == 0 || count < 0) {
    cout << "-1\n";
    return 0;
  }
  int array[length];
  for (int i = 0; i < length; ++i) array[i] = i + 1;
  Context ctx {
    .array = array,
    .gasRemaining = count - 1,
  };
  ctx.mergeShuffle(0, length);
  if (ctx.gasRemaining) {
    cout << "-1\n";
    return 0;
  }
#ifdef DEBUG
  ctx.mergeSort(0, length);
  cout << ctx.gasRemaining << ' ' << count << endl;
#endif
  for (int i = 0; i < length - 1; ++i) cout << array[i] << ' ';
  cout << array[length - 1] << endl;
  return 0;
}
