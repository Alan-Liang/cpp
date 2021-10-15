//
// Created by Rainy Memory on 2021/10/11.
//

#include <cstdio>
#include <random>
#include <ctime>

using namespace std;

int randomNumber() {
    static int lBound = -2147483648;
    static int uBound = 2147483647;
    static uint_fast32_t seed = time(nullptr);
    static default_random_engine eng(seed);
    static uniform_int_distribution<int> dist(lBound, uBound);
    return dist(eng);
}

int randomNumber(int bound) {
    return (randomNumber() % bound + bound) % bound;
}

int main() {
    int m, n, len;
    scanf("%d %d", &m, &n);
    printf("%d\n", m), len = m;
    while (m--) printf(m == 0 ? "%d\n" : "%d ", randomNumber());
    printf("%d\n", n);
    while (n--) {
        // 0 10%
        // 1 10%
        // 2 20%
        // 3 20%
        // 4 20%
        // 5 15%
        // 6  5%
        int seed = randomNumber(100);
        if (len < 10 || seed < 10) printf("0 %d %d\n", randomNumber(len++) + 1, randomNumber());
        else if (seed < 20) printf("1 %d\n", randomNumber(len--) + 1);
        else if (seed < 40) puts("2");
        else if (seed < 60) {
            int i = randomNumber(len * 2 / 3) + len * 1 / 3;
            len = i;
            printf("3 %d\n", i);
        }
        else if (seed < 80) printf("4 %d\n", randomNumber(len) + 1);
        else if (seed < 95) puts("5");
        else puts("6");
    }
    return 0;
}