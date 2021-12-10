#include <iostream>
#include "1048.h"

using std::cin, std::cout, std::endl;

void hello()
{
    std::cout << "Hello world!" << std::endl;
}

int main()
{
    int *p = new int [2];
    Defer defer([&](){delete [] p;});
    defer([&](){std::cout << p[0] << " " << p[1] << std::endl;});
    defer([&](){p[0] = 0, p[1] = 1;});
    defer(hello);
    p[0] = 2, p[1] = 3;
    return 0;
}
