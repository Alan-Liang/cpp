#include <iostream>
#include <cmath>

using namespace std;

struct Coordinate {
  double x;
  double y;
};

struct Circle {
  Coordinate center;
  double radius;
};

const int MAX_NUM = 10000;
int circleNumber = 0; // 目前存储的圆的数量
Circle circles[MAX_NUM];

void addCircle (Coordinate center, double radius) {
  circles[circleNumber].center = center;
  circles[circleNumber].radius = radius;
  circleNumber++;
}

void modifyCircle (int index, Coordinate center, double radius) {
  circles[index].center = center;
  circles[index].radius = radius;
}

void printCircle (Circle circle) {
  cout.setf(cout.fixed);
  cout.precision(3);
  cout << circle.center.x << ' ' << circle.center.y << ' ' << circle.radius << '\n';
}

bool intersect (Circle circle1, Circle circle2) {
  auto distance = sqrt(pow(circle1.center.x - circle2.center.x, 2) + pow(circle1.center.y - circle2.center.y, 2));
  auto sigmaR = circle1.radius + circle2.radius;
  auto deltaR = abs(circle1.radius - circle2.radius);
  return deltaR < distance && distance < sigmaR;
}

void traverse () {
  // 使用指针遍历数组
  for (Circle *ptr = circles; ptr != circles + circleNumber; ptr++) {
    printCircle(*ptr);
  }
}

int main () {
  int op, n;
  cin >> n;
  while (n--) {
    cin >> op;
    if (op == 1) {
      double x, y, r;
      cin >> x >> y >> r;
      Coordinate center;
      center.x = x;
      center.y = y;
      addCircle(center, r);
    } else if (op == 2) {
      int index;
      double x, y, r;
      cin >> index >> x >> y >> r;
      Coordinate center;
      center.x = x;
      center.y = y;
      modifyCircle(index, center, r);
    } else if (op == 3) {
      int index;
      cin >> index;
      printCircle(circles[index]);
    } else if (op == 4) {
      int index1, index2;
      cin >> index1 >> index2;
      if (intersect(circles[index1], circles[index2])) cout << "Yes" << endl;
      else cout << "No" << endl;
    } else if (op == 5) {
      traverse();
    }
  }
}
