#include<iostream>

#define EPSILON 0.001

inline int sgn (double x) {
  return x > EPSILON ? 1 : x < -EPSILON ? -1 : 0;
}

inline int side (double x1, double y1, double x2, double y2, double x, double y) {
  double delta = (x - x1) * (y - y2) - (x - x2) * (y - y1);
  return sgn(delta);
}

inline bool isIn (double x, double x1, double x2) {
  double t;
  if (x1 > x2) {
    t = x1; x1 = x2; x2 = t;
  }
  return x > x1 && x < x2;
}

int main () {
  double x[4], y[4];
  for (int i = 0; i < 4; i++) std::cin >> x[i] >> y[i];
  int s1 = side(x[0], y[0], x[1], y[1], x[3], y[3]);
  int s2 = side(x[0], y[0], x[2], y[2], x[3], y[3]);
  int s3 = side(x[1], y[1], x[2], y[2], x[3], y[3]);

  int d1 = side(x[0], y[0], x[1], y[1], x[2], y[2]);
  int d2 = side(x[0], y[0], x[2], y[2], x[1], y[1]);
  int d3 = side(x[1], y[1], x[2], y[2], x[0], y[0]);
  if (
    d1 == 0 || d2 == 0 || d3 == 0 ||
    (s1 == 0 && isIn(x[3], x[0], x[1])) ||
    (s2 == 0 && isIn(x[3], x[0], x[2])) ||
    (s3 == 0 && isIn(x[3], x[1], x[2]))
  ) {
    std::cout << "false\n";
    return 0;
  }
  bool inside = s1 == d1 && s2 == d2 && s3 == d3;
  std::cout << (inside ? "inside\n" : "outside\n");
  return 0;
}
