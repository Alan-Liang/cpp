#include <iostream>
#include <iomanip>
using namespace std;

class CircleSet {
    friend istream &operator>>(istream &in, CircleSet &obj);
    private:
        struct Circle {
            long long x, y, r;
            Circle(long long _x = 0, long long _y = 0, long long _r = 0): x(_x), y(_y), r(_r) {}
        };
        int count;//集合中圆的数目
        Circle *circles;//集合中所有圆
        long long quad_ (long long a) { return a * a; }
    public:
        CircleSet(int n): count(n) {
            circles = new Circle[n];
        }
        ~CircleSet () { delete[] circles; }
        long long operator[] (int i) { return circles[i].r; }
        bool checkContaining (int p, int q) {
          if (circles[p].r <= circles[q].r) return false;
          return quad_(circles[p].x - circles[q].x) + quad_(circles[p].y - circles[q].y) < quad_(circles[p].r - circles[q].r);
        }
        int getCircleContainingQ (int q) {
          int min = 19260817;
          for (int i = 0; i < count; ++i) if (checkContaining(i, q)) min = min > circles[i].r ? circles[i].r : min;
          return min;
        }
};

istream &operator>>(istream &in, CircleSet &obj) {
    for (int i = 0; i < obj.count; ++i) {
        in >> obj.circles[i].x >> obj.circles[i].y >> obj.circles[i].r;
    }
    return in;
}

#ifndef ONLINE_JUDGE
int main() {
    int n, m, type;
    cin >> n >> m;
    CircleSet set(n);
    cin >> set; //输入集合中的所有圆
    while (m--) {
        int type, p, q;
        cin >> type;
        if (type == 1) {
            //do nothing
        } else if (type == 2) {
            for (int i = 0; i < n; ++i) {
                cout << set[i] << ' ';
            }
            cout << endl;
        } else if (type == 3) {
            cin >> p >> q;
            cout << set.checkContaining(p, q) << endl;
        } else if (type == 4) {
            cin >> q;
            cout << set.getCircleContainingQ(q) << endl;
        }
    }
    return 0;
}
#endif
