#include <iostream>
#include <cstring>
using namespace std;

int n;
int *&funA (int **&ptr);
void funB (int *array, int **ptr1, int **ptr2);

int main () {
    int a[100], b[100], c[100];
    cin >> n;
    for (int i = 0;i < n; ++i)
        cin >> a[i];
    for (int i = 0;i < n; ++i)
        cin >> b[i];
    int **p,**q;
    funA(p) = a;
    funA(q) = b;
    funB(c,p,q);
    for (int i = 0; i < n; ++i)
        cout << c[i] << " ";
    return 0;
}

int *&funA (int **&ptr) {
  return reinterpret_cast<int *&>(ptr);
}
void funB (int *array, int **ptr1, int **ptr2) {
  for (int i = 0; i < 100; i++) {
    array[i] = reinterpret_cast<int *>(ptr1)[i] * reinterpret_cast<int *>(ptr2)[i];
  }
}
