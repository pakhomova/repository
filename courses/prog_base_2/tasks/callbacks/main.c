#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

typedef void (*equalCB) (int);
typedef int (*oppositeCB) (int, int, int);

int random () {
    return rand() % 101 - 50;
}

void equalFunc (int x) {
    printf ("Equal digit is %i\n", x);
}

int oppositeFunc (int x, int y, int sum) {
    if (x < 0) sum +=x;
        else sum +=y;
    printf ("Sum is %i\n", sum);
    return sum;
}

void randomness (equalCB equal, oppositeCB opposite) {
    srand(time(NULL));
    int sum = 0;
    while (!kbhit()) {
        Sleep (3);
        int x = random(), y = random();
        if (x == y) equal (x);
        if (x == -y) sum = opposite (x, y, sum);
    }
}

int main() {
    equalCB cb1 = equalFunc;
    oppositeCB cb2 = oppositeFunc;
    randomness(cb1, cb2);
    return 0;
}
