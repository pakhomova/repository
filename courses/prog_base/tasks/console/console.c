#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int colors(int x, int y){
    int color;
            if(x >= 0 && x <= 39 && x%3 == 0){
                color = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
            }
            else if(x >= 0 && x <= 39 && x%3 == 1){
                color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
            }
            else if(x >= 0 && x <= 39 && x%3 == 2){
                color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
            }
            else if(x >= 40 && x <= 79 && x%3 == 1){
                color = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
            }
            else if(x >= 40 && x <= 79 && x%3 == 0){
                color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
            }
            else if(x >= 40 && x <= 79 && x%3 == 2){
                color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
            }
return color;
}

int main(void){
const long SLEEP_MILLISECONDS = 50;
int x = 79, y = 24, color;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;
for(x = 79; x >= 0; x--){
    pos.X = x;
    if(x%2 == 1){
        y = 24;
        for(y = 24; y >= 0; y--){
            pos.Y = y;
            SetConsoleTextAttribute(hConsole, colors(x, y));
            SetConsoleCursorPosition(hConsole, pos);
            printf("*");
            Sleep(SLEEP_MILLISECONDS);
        }
    }
    else{
        y = 0;
        for(y = 0; y < 25; y++){
            pos.Y = y;
            SetConsoleTextAttribute(hConsole, colors(x, y));
            SetConsoleCursorPosition(hConsole, pos);
            printf("*");
            Sleep(SLEEP_MILLISECONDS);
        }
    }
}
return EXIT_SUCCESS;
}
