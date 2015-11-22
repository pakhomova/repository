#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define FWIDTH 1600
#define FHEIGHT 500

void axisPrinter(COORD centre){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int x = centre.X, y = centre.Y, x1 = 0, y1 = 0, color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, color);
	for (y1 = 24; y1 >=0; y1--){
		centre.Y = y1;
		SetConsoleCursorPosition(hConsole, centre);
		if (y1 % 5 == 0)
			printf("+");
		else printf("|");
	}
	for (x1 = 0; x1 < 80; x1++){
		centre.X = x1;
		centre.Y = y;
		SetConsoleCursorPosition(hConsole, centre);
		if (x1 % 4 == 0)
			printf("+");
		else printf("-");
	}
}

void pointPrinter(COORD centre, double x, double y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	centre.X += x / FWIDTH * 80;
	centre.Y += y / FHEIGHT * 25;
	if (centre.X >= 0 && centre.X <= 79 && centre.Y >= 0 && centre.Y <= 24) {
		SetConsoleCursorPosition(hConsole, centre);
		printf(" ");
	}
}

void background(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int background_color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY, x, y;
	SetConsoleTextAttribute(hConsole, background_color);
	system("cls");
}

void functions(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int color1 = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		color2 = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	pos.X = 1;
	pos.Y = 1;
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, color1);
	printf("F(x) = x^1.5 + 2 * x - 3;");
	pos.X = 1;
	pos.Y = 2;
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, color2);
	printf("F(x) = 0.3 * tg(x) + 2;");
}


void fGraph1(COORD center, double k){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int background_color = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, background_color);
	int x, y;
	for (x = -FWIDTH/2; x < FWIDTH/2; x++) {
		y = - (pow(abs(x / k), 1.5) + 2 * x / k - 3) / k; //  (pow(abs(x / k), 1.5) + 2 * x * k - 3) * k;
		pointPrinter(center, x/k, y);
	}
}


void fGraph2(COORD center, double k){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={0,0};
	int background_color = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, background_color);
	int x, y;
	for (x = -FWIDTH/2; x < FWIDTH/2; x++) {
		y = -(0.3 * tan(x / k) + 2) * k;
		pointPrinter(center, x, y);
	}
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, 255);
	printf(" ");
}

void moving(COORD centre, double k){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int input = 0;
	while (input != 27){
		input = getch();
		background();
		switch (input)
		{
		case 'w':
			centre.Y--;
			axisPrinter(centre);
			functions();
			break;
		case 's':
			centre.Y++;
			axisPrinter(centre);
			functions();
			break;
		case 'd':
			centre.X++;
			axisPrinter(centre);
			functions();
			break;
		case 'a':
			centre.X--;
			axisPrinter(centre);
			functions();
			break;
		case '-':
			axisPrinter(centre);
			functions();
			if(k > 10)
				k = k - 10;
			break;
		case '+':
			axisPrinter(centre);
			functions();
			k = k + 10;
			break;
		}
		fGraph2(centre, k);
        fGraph1(centre, k/10);
	}
}


int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int k = 50;
	background();
	pos.X = 39;
	pos.Y = 12;
	axisPrinter(pos);
	functions();
	fGraph2(pos, k);
	fGraph1(pos, k/10);
	moving(pos, k);
	return EXIT_SUCCESS;
}
