#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <vector>
using namespace std;
CONST short MainMenu = 0;
CONST short button1 = 1;
CONST short button2 = 2;
CONST short button3 = 3;
CONST int CountOfMenu = 4;
CONST int CountOfButtons = 3;
string mas[CountOfMenu][CountOfButtons] = {
	{"*Button1*", " Button2 ", " Button3 " },
	{ "*Punkt11*", " Punkt12 ", " Punkt13 " },
	{ "*Punkt21*", " Punkt22 ", " Punkt23 " },
	{ "*Punkt31*", " Punkt32 ", " Punkt33 " }
};
void Buttons(short variantofbutton);
void defaultt();
void peremeshenie(short index, short ACTUALMENUPOSITION, short posx, short posy, short variantofmap);
void navigate(short beforeposition, short afterposition, short& posx, short& posy, short variantofmap)
{
	string s;
	string news;
	s = mas[variantofmap][beforeposition];
	s[0] = ' '; s[s.size() - 1] = ' ';
	news = mas[variantofmap][afterposition];
	news[0] = '*'; news[news.size() - 1] = '*';
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	cout << s << endl;
	if (afterposition > beforeposition) {
		if (beforeposition == 0 && afterposition == 2)
		{
			posy++;
			posy++;
		}
		else  posy++;
	}
	else {
		if (beforeposition == 2 && afterposition == 0)
		{
			posy--;
			posy--;
		}
		else posy--;
	}
	pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	cout << news << endl;
	Sleep(500u);
}
void Buttons(short variantofbutton) {
	int index;
	system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 40, 10 };
	for (int i = 0; i < CountOfButtons; i++) {
		SetConsoleCursorPosition(hOut, pos);
		cout << mas[variantofbutton][i] << endl;
		pos.Y++;
	}
	short ACTUALMENUPOSITION = 0;
	pos.Y = 10;
	peremeshenie(0, ACTUALMENUPOSITION, pos.X, pos.Y, variantofbutton);
}
void peremeshenie(short index, short ACTUALMENUPOSITION, short posx, short posy, short variantofmap) {
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN)) {
			index = (ACTUALMENUPOSITION + 1) % 3;
			navigate(ACTUALMENUPOSITION, index, posx, posy, variantofmap);
			ACTUALMENUPOSITION = index;
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			if (ACTUALMENUPOSITION == 0) {
				index = 2;
			}
			else index = (ACTUALMENUPOSITION - 1);
			navigate(ACTUALMENUPOSITION, index, posx, posy, variantofmap);
			ACTUALMENUPOSITION = index;
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {
			if (variantofmap == button1 || variantofmap == button2 || variantofmap == button3)
				defaultt();
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (variantofmap == button1) {
				if (posy == 10) Buttons(button1);
				if (posy == 11) Buttons(button2);
				if (posy == 12) Buttons(button3);
			}
		}
	}
}
void defaultt() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 40, 10 };
	for (int i = 0; i < CountOfButtons; i++)
	{
		SetConsoleCursorPosition(hOut, pos);
		cout << mas[0][i] << endl;
		pos.Y++;
	}
	short ACTUALMENUPOSITION = 0;
	pos.Y = 10;
	peremeshenie(0, ACTUALMENUPOSITION, pos.X, pos.Y, MainMenu);
}
int main()
{
	defaultt();
}
