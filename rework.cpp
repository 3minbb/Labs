#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <conio.h>
#include <vector>
using namespace std;

void peremeshenie(short index, short ACTUALMENUPOSITION, short posx, short posy, string* textredactor, int countofsymbols, int starstroka, int beforestar, char** starredact);
string* increase(string* textredactor, int newSize)
{
	string* newArr = new string[newSize];
	delete[] textredactor;
	return newArr;
}
int main()
{
	ifstream text("F:\\textred.txt");
	string s;
	char temp;
	if (!text) {
		cerr << "File error." << endl;
		return 1;
	}
	text.unsetf(ios::skipws);
	while (text >> temp)
		s += temp;
	int countofsymbols = s.size();
	string* textredactor = new string[countofsymbols];
	for (int i = 0; i < countofsymbols; i++)
		textredactor[i] = s[i];
	int countofstring;
	countofstring = (s.size() / 20) + 1;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 40, 10 };

	for (int i = 0; i < countofsymbols; i++)
	{
		if (i % 20 == 0 && i != 0) {
			pos.X = 40;
			pos.Y++;
			pos.Y++;
		}
		SetConsoleCursorPosition(hOut, pos);
		cout << textredactor[i];
		pos.X++;
	}
	pos.X = 40;
	pos.Y = 10;
	short ACTUALMENUPOSITION = 0;
	int countstar = countofstring * 2;
	int N = 20;
	int i;
	char** starredact;
	starredact = new char* [40];
	for (i = 0; i < 40; i++)
		starredact[i] = new char[N];
	peremeshenie(0, ACTUALMENUPOSITION, pos.X, pos.Y, textredactor, countofsymbols, 2, 2, starredact);
	system("Pause");
	return 0;
}
void navigate(short beforeposition, short afterposition, short& posx, short& posy, int& starstroka, int& beforestar, char** starredact, int& nowstring)
{
	string s;
	string news;
	s = starredact[beforestar][beforeposition] = ' ';
	news = starredact[starstroka][afterposition] = '*';
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { posx, posy };
	COORD star = { posx, posy + 1 };
	SetConsoleCursorPosition(hOut, star);
	cout << s;
	if (afterposition > beforeposition) {
		if (afterposition % 20 == 0 && (beforeposition+1) % 20 == 0) {
			nowstring++;
			posx = 40;
		}
		else posx++;
	}
	else if (afterposition < beforeposition) {
		if (beforeposition % 20 == 0 && (afterposition+1) % 20 == 0) {
			posx = 59;
			nowstring--;
		}
		else posx--;
	}
	if (beforestar < starstroka) {
		posy += 2;
	}
	else if (beforestar > starstroka) {
		posy -= 2;
	}
	star = { posx, posy + 1 };
	SetConsoleCursorPosition(hOut, star);
	cout << news;
	Sleep(500u);
}
void peremeshenie(short index, short ACTUALMENUPOSITION, short posx, short posy, string* textredactor, int countofsymbols, int starstroka, int beforestar, char** starredact) {
	starredact[0][1] = '*';
	int nowstring = 1;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD star = { posx, posy + 1 };
	SetConsoleCursorPosition(hOut, star);
	cout << starredact[0][1];
	int x;
	int countofstring;
	while (true)
	{
		x = _getch();
		if (x == 224) {
			x = _getch();
			if (x == 80) {
				if ((index + 20) < countofsymbols) {
					nowstring++;
					index = ACTUALMENUPOSITION;
					starstroka = beforestar + 1;
					navigate(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
					index += 20;
					ACTUALMENUPOSITION = index;
					beforestar = starstroka;
				}
			}
			else if (x == 72)
			{
				if (nowstring > 1 && index < countofsymbols) {
					nowstring--;
					index = ACTUALMENUPOSITION;
					starstroka = beforestar - 1;
					navigate(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
					index -= 20;
					ACTUALMENUPOSITION = index;
					beforestar = starstroka;
				}
			}
			else if (x == 77)
			{
				if (index != (countofsymbols - 1)) {
					index = ACTUALMENUPOSITION + 1;
					if ((ACTUALMENUPOSITION + 1) % 20 == 0 && ACTUALMENUPOSITION != 0) starstroka++;
					navigate(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
					ACTUALMENUPOSITION = index;
					beforestar = starstroka;
				}
			}
			else if (x == 75)
			{
				if (index != 0) {
					index = ACTUALMENUPOSITION - 1;
					if (ACTUALMENUPOSITION % 20 == 0) starstroka--;
					navigate(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
					ACTUALMENUPOSITION = index;
					beforestar = starstroka;
				}
			}
		}
		else if (x==27) {
			ofstream fout("F:\\textred.txt");
			for (int i = 0; i < countofsymbols; i++) {
				fout << textredactor[i];
			}
			fout.close();
				for (int i = 0; i < 40; i++)
				{
					delete[] starredact[i];
				}
			delete[] starredact;
			exit(EXIT_SUCCESS);
		}
		else if (isprint(x)) {
			string temp;
			int counter;
			
			for (counter = 0; counter < index; counter++)
				temp += textredactor[counter];
			temp += x;
			for (; counter < countofsymbols; counter++)
				temp += textredactor[counter];
			countofsymbols++;
			textredactor = (increase(textredactor, countofsymbols));
			for (int i = 0; i < countofsymbols; i++)
				textredactor[i] = temp[i];
			countofstring = (temp.size() / 20) + 1;
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD pos = { 40, 10 };
			for (int i = 0; i < countofsymbols; i++)
			{
				if (i % 20 == 0 && i !=0) {
					pos.X = 40;
					pos.Y++;
					pos.Y++;
				}
				SetConsoleCursorPosition(hOut, pos);
				cout << textredactor[i];
				pos.X++;
			}
			if (index != (countofsymbols - 1)) {
				index = ACTUALMENUPOSITION + 1;
				if ((ACTUALMENUPOSITION + 1) % 20 == 0 && ACTUALMENUPOSITION != 0) starstroka++;
				navigate(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
				ACTUALMENUPOSITION = index;
				beforestar = starstroka;
			}
		}
		else if (x == 8) {
			string temp;
			int counter;
			for (counter = 0; counter < index; counter++)
				temp += textredactor[counter];
			counter++;
			for (; counter < countofsymbols; counter++)
				temp += textredactor[counter];
			countofsymbols--;
			textredactor = (increase(textredactor, countofsymbols));
			for (int i = 0; i < countofsymbols; i++)
				textredactor[i] = temp[i];
			countofstring = (temp.size() / 20) + 1;
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD pos = { 40, 10 };
			int i;
			for (i = 0; i < countofsymbols; i++)
			{
				if (i % 20 == 0 && i != 0) {
					pos.X = 40;
					pos.Y++;
					pos.Y++;
				}
				SetConsoleCursorPosition(hOut, pos);
				cout << textredactor[i];
				pos.X++;
			}
			i++;
			if (i % 20 == 0 && i != 0) {
				pos.X = 40;
				pos.Y++;
				pos.Y++;
			}
			SetConsoleCursorPosition(hOut, pos);
			cout << " ";
			if ((countofsymbols+1) % 19 == 0 || ((countofsymbols+1) % 20) % 19 == 0) {
				int del = (countofsymbols+2) / 20;
				pos.Y = 10;
				pos.X = 60;
				SetConsoleCursorPosition(hOut, pos);
				cout << " ";
			}
		}
	}
}
