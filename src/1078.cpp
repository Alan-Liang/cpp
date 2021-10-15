// Accepted!

#include<iostream>
using namespace std;

#define MAXN 10000000
#define MAXP 10000000
#define MAXV 10000000

#define loop(max, i) for(int i=0;i<max;i++)

int p[MAXN], v[MAXN];
int n;

void read () {
  ios_base::sync_with_stdio(false);
  cin >> n;
  if (n > MAXN) while (true);
  loop (n, i) cin >> p[i] >> v[i];
  loop (n, i) if (p[i] > MAXP || v[i] > MAXV) while (true);
}

int emulate () {
  int current_speed = 2147483647;
  int groups = 0;
  loop (n, j) {
    int i = n - j - 1;
    if (v[i] <= current_speed) {
      groups++;
      current_speed = v[i];
    }
  }
  return groups;
}

int main () {
  read();
  cout << emulate() << endl;
  return 0;
}
