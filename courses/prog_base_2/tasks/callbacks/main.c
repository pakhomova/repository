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

void equalFunc1 (int x) {
    printf ("Equal!");
}

int oppositeFunc (int x, int y, int sum) {
    if (x < 0) sum +=x;
        else sum +=y;
    printf ("Sum is %i\n", sum);
    return sum;
}

int oppositeFunc1 (int x, int y, int sum) {
    printf ("Opposite!");
    return 0;
}

void randomness (equalCB equal, oppositeCB opposite) {
    int sum = 0;
    while (!kbhit()) {
        Sleep (3);
        int x = random(), y = random();
        if (x == y) equal (x);
        if (x == -y) sum = opposite (x, y, sum);
    }
    getch();
}

int main() {
    srand(time(NULL));
    equalCB cb1 = equalFunc;
    oppositeCB cb2 = oppositeFunc;
    equalCB cbAlternative1 = equalFunc1;
    oppositeCB cbAlternative2 = oppositeFunc1;
    randomness(cb1, cb2);
    randomness(cbAlternative1, cbAlternative2);
    return 0;
}
