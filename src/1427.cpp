#include "1427.hpp"
#include<iostream>

using namespace std;

int main() {
    puts("First, have some simple operation just like std::vector.");
    pylist ls;
    ls.append(1);
    cout << ls[0] << endl; // 1
    ls.append(2);
    cout << ls[1] << endl; // 2
    ls.pop();
    ls.append(3);
    cout << ls[1] << endl; // 3 (Now, ls == [1, 3])
    puts("After warming up exercise, your assignment operator will be tested.");
    puts("Now we will test whether your assignment operator will pass by reference.");
    pylist ls2 = ls;
    ls.append(4);
    cout << ls2[2] << endl; // 4 (Now, ls == ls2 == [1, 3, 4]) (Because assignment operator pass by reference. We will not mention this afterward.)
    ls.pop();
    ls2.append(5);
    cout << ls[2] << endl; // 5 (Now, ls == ls2 == [1, 3, 5])
    puts("Now we will test whether your pylist enable nesting.");
    pylist ls3;
    ls3.append(6);
    ls[0] = ls3;
    cout << ls2[0][0] << endl;// 6 (Now, ls == ls2 == [[6], 3, 5])
    ls2.append(ls3);
    ls2[3].append(7);
    ls[1] = pylist();
    cout << ls[0][1] << endl; // 7 (Now, ls == ls2 == [[6, 7], [], 5, [6, 7]])
    ls2[2] = ls[1];
    ls2[1].append(8);
    cout << ls2[2][0] << endl; // 8 (Now, ls == ls2 == [[6, 7], [8], [8], [6, 7]], ls3 = [6, 7])
    puts("Robust test now.");
    ls[0] = pylist();
    ls2 = ls;
    ls3 = ls3; //(Now, ls == ls2 == [[], [8], [8], [6, 7]], ls3 = [6, 7])
    ls2 = ls3; //(Now, ls == [[], [8], [8], [6, 7]], ls2 == ls3 = [6, 7])
    ls3[0] = ls3; // (ls3 is being referenced by itself)
    ls2.append(3*3); //(Now, ls == [[], [8], [8], [[...], 7, 9]], ls2 == ls3 = [[...], 7, 9])
    cout << ls[3][0][0][0][0][0][0][0][0][0][0][0][0][2] << endl; // 9
    puts("Finally!");
    cout << 2 * ls[3][0][2] + (ls2[1] << 1 >> 1) - (1 ^ ls2[2] ^ 1) - (ls2[1] / 1) - (ls[1][0] % 8) + 1 << endl; // 10
    cout << ls << endl; // [[], [8], [8], [[...], 7, 9]]
    cout << ls.pop() << endl; // [[...], 7, 9]
    cout << 0 + ls[2].pop() << endl; // 8
    cout << ls << endl; // [[], [], []]
}
