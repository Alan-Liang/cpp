#include<iostream>
#include<fstream>
using namespace std;
int main () {
  int a;
  cin >> a;
  cout << cin.fail() << " ";
  cout << a << endl;

  cin.clear();
  cin.get();

  cin >> a;
  cout << cin.fail() << " ";
  cout << a << endl;
}
