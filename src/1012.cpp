#include<iostream>
using namespace std;

#define MAXN 100000
#define loop(max, i) for(int i=0;i<max;i++)

int height[MAXN];
int n, m;

void read () {
  cin >> n >> m;
  int i, h;
  loop (m, j) {
    cin >> i >> h;
    height[i] = h;
    int num = 0;
    float deg = 0;
    // TODO: cache
    loop (n, k) {
      if (height[k] == 0) continue;
      float degk = height[k] / (float) k;
      if (degk - deg > 0.001f) {
        num++;
        deg = degk;
      }
    }
    cout << num << endl;
  }
}

void clear () {
  loop (MAXN, i) height[i] = 0;
}

int main () {
  int T;
  ios_base::sync_with_stdio(false);
  cin >> T;
  loop (T, i) {
    if (i != 0) clear();
    read();
  }
  return 0;
}
