#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
void fillRand(int n, int m, int mat[n][m], int diapason1, int diapason2) {
int i, j, a;
if (diapason1 == diapason2){
for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < m; j++ ) {
      mat[i][j] = diapason1;
        }
    }
}
if(diapason1 > diapason2){
    a = diapason2;
    diapason2 = diapason1;
    diapason1 = a;
}
for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < m; j++ ) {
      mat[i][j] = (rand()%(diapason2 - diapason1 + 1) + diapason1);
        }
    }
}

void baseprint(int x, int y, int color){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;
pos.X = x;
pos.Y = y;
SetConsoleCursorPosition(hConsole, pos);
SetConsoleTextAttribute(hConsole, color);
}

void deleting(y){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;
int x;
for(x = 1; x < 80; x++){
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    printf(" ");
    }
}

void background(void){
int background_color1 = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY, x, y,
background_color2 = BACKGROUND_BLUE | BACKGROUND_INTENSITY,
accessories = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
for(x = 0; x < 80; x++){
    for(y = 0; y < 14; y++){
    baseprint(x, y, background_color1);
    printf(" ");
    baseprint(0, y, accessories);
    printf(":");
    baseprint(79, y, accessories);
    printf(":");
    }
    for(y = 14; y < 25; y++){
    baseprint(x, y, background_color2);
    printf(" ");
    }
    baseprint(x, 0, accessories);
    printf(":");
    baseprint(x, 13, accessories);
    printf(":");
}
}

void printMatrix(int n, int m, int mat[n][m]){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;
int color = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
SetConsoleTextAttribute(hConsole, color);
pos.X = (79 - 4*m)/2;
pos.Y = 2;
SetConsoleCursorPosition(hConsole, pos);
int i, j;
for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < m; j++ ) {
      printf("%4i", mat[i][j]);
        }
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    }
}

void hello(void){
int color = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
baseprint(25, 7, color);
printf("Hello! Press any key to CONTINUE");
getch();
}
int isNumber(char* str){
int i;
    for(i=0; i<strlen(str); i++){
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}
int firstEnter1(void){
char temp[50];
int color = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
baseprint(25, 4, color);
printf("Matrix size is a*b.");
baseprint(25, 5, color);
printf("Enter a [1 ; 10] : ");
baseprint(25, 6, color);
while(scanf("%s", temp) != 1 || isNumber(temp) == 0 || atoi(temp) > 10 || atoi(temp) < 1){
    fflush(stdin);
    baseprint(25, 7, color);
    printf(" ERROR, try again!");
    deleting(6);
    baseprint(25, 6, color);
}
deleting(7);
return atoi(temp);
}

int firstEnter2(void){
int color = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
int b = 0;
char temp[50];
baseprint(25, 8, color);
printf("Enter b [1 ; 10] : ");
baseprint(25, 9, color);
while(scanf("%s", temp) != 1 || isNumber(temp) == 0 || atoi(temp) > 10 || atoi(temp) < 1){
    fflush(stdin);
    baseprint(25, 10, color);
    printf(" ERROR, try again!");
    deleting(9);
    baseprint(25, 9, color);
}
deleting(10);
return atoi(temp);
}


void help(){
int yellow = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
baseprint(1, 17, yellow);
printf("end - end of process");
baseprint(1, 18, yellow);
printf("null - clear all elements");
baseprint(1, 19, yellow);
printf("flipH - horizontal flip");
baseprint(1, 20, yellow);
printf("mean - mean value of elements");
baseprint(1, 21, yellow);
printf("change - replace the element with entered value");
baseprint(1, 22, yellow);
printf("random - fill with random digits");
baseprint(1, 23, yellow);
printf("change3 - replace min sum elements column with max sum elements column");
baseprint(31, 17, yellow);
printf("sum - sum of the specified column elements");
baseprint(31, 18, yellow);
printf("change1 - replace first min with last max element");
baseprint(31, 19, yellow);
printf("change2 - replace last min with last max element");
}

void end(){
exit(0);
}

void null(int n, int m, int mat[n][m]){
int i, j;
for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < m; j++ ) {
      mat[i][j] = 0;
        }
    }
printMatrix(n, m, mat);
}

void newcommand(){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int y, delcolor = BACKGROUND_BLUE | BACKGROUND_INTENSITY, yellow = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
SetConsoleTextAttribute(hConsole, delcolor);
deleting(16);
for(y = 17; y < 25; y++){
    deleting(y);
    }
baseprint(2, 16, yellow);
}

void flipH(int n, int m, int mat[n][m]){
int i, j, a;
for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n/2; j++ ) {
        a = mat[i][(m-1)-j];
        mat[i][(m-1)-j] = mat[i][j];
        mat[i][j] = a;
        }
    }
printMatrix(n, m, mat);
}

int randomenter1(void){
int color = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
char temp[50];
baseprint(2, 18, color);
printf("Diapason is [a , b]");
baseprint(2, 19, color);
printf("Enter a [-100 ; 100] : ");
baseprint(2, 20, color);
while(scanf("%s", temp) != 1 || isNumber(temp) == 0 || atoi(temp) > 100 || atoi(temp) < -100){
    fflush(stdin);
    baseprint(2, 21, color);
    printf(" ERROR, try again!");
    deleting(20);
    baseprint(2, 20, color);
}
deleting(21);
return atoi(temp);
}

int randomenter2(void){
int color = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
char temp[50];
baseprint(2, 21, color);
printf("Enter b [-100 ; 100] : ");
baseprint(2, 22, color);
while(scanf("%s", temp) != 1 || isNumber(temp) == 0 || atoi(temp) > 100 || atoi(temp) < -100){
    fflush(stdin);
    baseprint(2, 23, color);
    printf(" ERROR, try again!");
    deleting(22);
    baseprint(2, 22, color);
}
deleting(23);
return atoi(temp);
}

void random(int n, int m, int mat[n][m]){
int a, b, ind;
a = randomenter1();
b = randomenter2();
fillRand(n, m, mat, a, b);
printMatrix(n, m, mat);
}

int changeenter1(int n, int m){
int color = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
char temp[50];
baseprint(2, 18, color);
printf("Replace the element [a][b] with value c");
baseprint(2, 19, color);
printf("Enter a [0 ; %i] : ", n - 1);
baseprint(2, 20, color);
while(scanf("%s", temp) != 1 || isNumber(temp) == 0 || atoi(temp) > n - 1 || atoi(temp) < 0){
    fflush(stdin);
    baseprint(2, 21, color);
    printf(" ERROR, try again!");
    deleting(20);
    baseprint(2, 20, color);
}
deleting(21);
return atoi(temp);
}

int changeenter2(int n, int m){
int color = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
char temp[50];
baseprint(2, 21, color);
printf("Enter b [0 ; %i] : ", m - 1);
baseprint(2, 22, color);
while(scanf("%s", temp) != 1 || isNumber(temp) == 0 || atoi(temp) > m - 1 || atoi(temp) < 0){
    fflush(stdin);
    baseprint(2, 23, color);
    printf(" ERROR, try again!");
    deleting(22);
    baseprint(2, 22, color);
}
deleting(23);
return atoi(temp);
}

int changeenter3(void){
int x, color = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
char temp[50];
baseprint(42, 19, color);
printf("Enter c [-50 ; 50] :");
baseprint(42, 20, color);
while(scanf("%s", temp) != 1 || isNumber(temp) == 0 || atoi(temp) > 50 || atoi(temp) < -50){
    fflush(stdin);
    baseprint(42, 21, color);
    printf(" ERROR, try again!");
    for(x = 42; x < 80; x++){
        baseprint(x, 20, color);
        printf(" ");
    }
    baseprint(42, 20, color);
}
deleting(21);
return atoi(temp);
}

void elchange(int n, int m, int mat[n][m]){
int ind1, ind2, value;
ind1 = changeenter1(n, m);
ind2 = changeenter2(n, m);
value = changeenter3();
mat[ind1][ind2] = value;
printMatrix(n, m, mat);
}

void meanValue(int n, int m, int mat[n][m]){
double mv;
int k = 0, i, j, color = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < m; j++ ){
        k = k + mat[i][j];
        }
    }
mv = (double)k/(double)(m*n);
baseprint(2, 18, color);
printf("Mean value is %f", mv);
}

void elementsSum(int n, int m, int mat[n][m]){
int i, sum = 0, indM, color = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
char temp[50];
baseprint(2, 18, color);
printf("Enter the index of column [0 ; %i] : ", m - 1);
baseprint(2, 19, color);
while(scanf("%s", temp) != 1 || isNumber(temp) == 0 || atoi(temp) > m - 1 || atoi(temp) < 0){
    fflush(stdin);
    baseprint(2, 20, color);
    printf(" ERROR, try again!");
    deleting(19);
    baseprint(2, 19, color);
}
deleting(20);
indM = atoi(temp);
for(i = 0; i < n; i++){
    sum = sum + mat[i][indM];
}
baseprint(2, 20, color);
printf("Sum of the specified column elements is : %i", sum);
}

void elementsChange1(int n, int m, int mat[n][m]){         //меняет местами первый минимальный и последний максимальный
int i, j, min = mat[n - 1][m - 1], max = mat[0][0], indNmax = 0, indMmax = 0, indNmin = n - 1, indMmin = m - 1, a;
for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < m; j++ ){
        if(mat[i][j] >= max){
            max = mat[i][j];
            indNmax = i;
            indMmax = j;
            }
        }
    }
for(i = n - 1; i >= 0; i--){
    for(j = m - 1; j >=0; j--){
        if(mat[i][j] <= min){
            min = mat[i][j];
            indNmin = i;
            indMmin = j;
            }
        }
    }
a = mat[indNmax][indMmax];
mat[indNmax][indMmax] = mat[indNmin][indMmin];
mat[indNmin][indMmin] = a;
printMatrix(n, m, mat);
}

void elementsChange2(int n, int m, int mat[n][m]){         //меняет местами последний минимальный и последний максимальный
int i, j, min = mat[0][0], max = mat[0][0], indNmin = 0, indMmin = 0, indNmax = 0, indMmax = 0, a;
for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < m; j++ ){
        if(mat[i][j] <= min){
            min = mat[i][j];
            indNmin = i;
            indMmin = j;
            }
        }
    }
for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < m; j++ ){
        if(mat[i][j] >= max){
            max = mat[i][j];
            indNmax = i;
            indMmax = j;
            }
        }
    }
a = mat[indNmax][indMmax];
mat[indNmax][indMmax] = mat[indNmin][indMmin];
mat[indNmin][indMmin] = a;
printMatrix(n, m, mat);
}

void columnChange(int n, int m, int mat[n][m]){
int i, j, sum = 0, sumMax = 0, sumMin = 0, columnMax = 0, columnMin = 0, a;
for(i = 0; i < n; i++){
    sumMax = sumMax + mat[i][0];
    sumMin = sumMin + mat[i][0];
}
for(j = 1; j < m; j++){
    sum = 0;
    for(i = 0; i < n; i++){
        sum = sum + mat[i][j];
        }
    if(sum  > sumMax){
        sumMax = sum;
        columnMax = j;
        }
    if(sum < sumMin){
        sumMin = sum;
        columnMin = j;
        }
    }
for(i = 0; i < n; i++){
    a = mat[i][columnMax];
    mat[i][columnMax] = mat[i][columnMin];
    mat[i][columnMin] = a;
    }
printMatrix(n, m, mat);
}

int command(int n, int m, int mat[n][m]){
int pink = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
green = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
yellow = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
int command = 0, y;
char s[50];
baseprint(2, 15, pink);
printf("Please, enter your command :");
while(command != 2){
baseprint(2, 16, yellow);
scanf("%s", s);
fflush(stdin);
if(strcmp(s,"help") == 0){
    command = 1;
}
else if(strcmp(s,"end") == 0){
    command = 2;
}
else if(strcmp(s,"null") == 0){
    command = 3;
}
else if(strcmp(s,"random") == 0){
    command = 4;
}
else if(strcmp(s,"change") == 0){
    command = 5;
}
else if(strcmp(s,"flipH") == 0){
    command = 6;
}
else if(strcmp(s,"mean") == 0){
    command = 7;
}
else if(strcmp(s,"sum") == 0){
   command = 8;
}
else if(strcmp(s,"change1") == 0){
    command = 9;
}
else if(strcmp(s,"change2") == 0){
    command = 10;
}
else if(strcmp(s,"change3") == 0){
    command = 11;
}
else{
    command = 0;
    baseprint(2, 17, pink);
    printf(" ERROR, try again!");
    deleting(16);
    baseprint(2, 16, pink);
    getch();
}
deleting(17);
switch (command){
    case 1:
        help();
        getch();
        break;
    case 2:
        end();
        break;
    case 3:
        null(n, m, mat);
        break;
    case 4:
        random(n, m, mat);
        break;
    case 5:
        elchange(n, m, mat);
        break;
    case 6:
        flipH(n, m, mat);
        break;
    case 7:
        meanValue(n, m, mat);
        getch();
        break;
    case 8:
        elementsSum(n, m, mat);
        getch();
        break;
    case 9:
        elementsChange1(n, m, mat);
        break;
    case 10:
        elementsChange2(n, m, mat);
        break;
    case 11:
        columnChange(n, m, mat);
        break;
    case 0:
        break;
}
newcommand();
}
}

int main(void){
srand((unsigned)time(NULL));
int n, m, c;
background();
hello();
background();
n = firstEnter1();
m = firstEnter2();
background();
int mat[n][m];
fillRand(n, m, mat, -50, 50);
printMatrix(n, m, mat);
command(n, m, mat);
getch();
return EXIT_SUCCESS;
}
