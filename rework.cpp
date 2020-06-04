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
const short stringsymbols = 20;
string mas[2] = {
	{"*Open file*"},
	{" Create new file "}
};
const short down = 80;
const short rightt = 77;
const short up = 72;
const short leftt = 75;
const short save = 27;
const short  backspace = 8;
string file_name;
void peremeshenie(short index, short ACTUALMENUPOSITION, short posx, short posy, string* textredactor, int countofsymbols, int starstroka, int beforestar, char** starredact);
void navigate(short beforeposition, short afterposition, short& posx, short& posy, int& starstroka, int& beforestar, char** starredact, int& nowstring);
void open_file(string& s, char& temp);
void new_file(string& s, char& temp);
void filechange(string& s, char& temp);
void filenavigate(short beforeposition, short afterposition, short& posx, short& posy)
{
	string s;
	string news;
	s = mas[beforeposition];
	s[0] = ' '; s[s.size() - 1] = ' ';
	news = mas[afterposition];
	news[0] = '*'; news[news.size() - 1] = '*';
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	cout << s << endl;
	if (afterposition > beforeposition) {
		if (beforeposition == 0 && afterposition == 1)
		{
			posy++;
		}
		else  posy++;
	}
	else {
		if (beforeposition == 1 && afterposition == 0)
		{
			posy--;
		}
		else posy--;
	}
	pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	cout << news << endl;
	Sleep(500u);
}
void filemenu(short index, short ACTUALMENUPOSITION, short posx, short posy, string& s, char& temp) {
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN)) {
			index = (ACTUALMENUPOSITION + 1) % 2;
			filenavigate(ACTUALMENUPOSITION, index, posx, posy);
			ACTUALMENUPOSITION = index;
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			if (ACTUALMENUPOSITION == 0) {
				index = 1;
			}
			else index = (ACTUALMENUPOSITION - 1);
			filenavigate(ACTUALMENUPOSITION, index, posx, posy);
			ACTUALMENUPOSITION = index;
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (posy == 10) {
				 open_file(s, temp);
				 system("cls");
				 break;
			}
			if (posy == 11) { 
				new_file(s, temp);
				system("cls");
				break;
			}
		}
	}
}
void open_file(string& s, char& temp) {
	//"F:\\textred.txt"
	system("cls");
	cout << "Enter file name: "; cin >> file_name;
	ifstream text;
	do {
		text.open(file_name);
		if (text.good())
			break;
		else {
			system("cls");
			cout << "\nFile error.\n"
				<< "Enter file name: ";
			cin >> file_name;
		}
	} while (true);
	text.unsetf(ios::skipws);
	while (text >> temp)
		s += temp;
}
void new_file(string& s, char& temp) {
	s = " ";
}
void filechange(string& s, char& temp) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 40, 10 };
	for (int i = 0; i < 2; i++)
	{
		SetConsoleCursorPosition(hOut, pos);
		cout << mas[i] << endl;
		pos.X = 40;
		pos.Y++;
	}
	short ACTUALMENUPOSITION = 0;
	pos.Y = 10;
	filemenu(0, ACTUALMENUPOSITION, pos.X, pos.Y, s, temp);

}

void downg(short& ACTUALMENUPOSITION,short& index,short& posx,short& posy,int& starstroka,int& beforestar,char** starredact,int& nowstring) {
	nowstring++;
	index = ACTUALMENUPOSITION;
	starstroka = beforestar + 1;
	navigate(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
	index += stringsymbols;
	ACTUALMENUPOSITION = index;
	beforestar = starstroka;
}
void upg(short& ACTUALMENUPOSITION, short& index, short& posx, short& posy, int& starstroka, int& beforestar, char** starredact, int& nowstring) {
	nowstring--;
	index = ACTUALMENUPOSITION;
	starstroka = beforestar - 1;
	navigate(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
	index -= stringsymbols;
	ACTUALMENUPOSITION = index;
	beforestar = starstroka;
}
void rightg(short& ACTUALMENUPOSITION, short& index, short& posx, short& posy, int& starstroka, int& beforestar, char** starredact, int& nowstring) {
	index = ACTUALMENUPOSITION + 1;
	if ((ACTUALMENUPOSITION + 1) % stringsymbols == 0 && ACTUALMENUPOSITION != 0) starstroka++;
	navigate(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
	ACTUALMENUPOSITION = index;
	beforestar = starstroka;
}
void leftg(short& ACTUALMENUPOSITION, short& index, short& posx, short& posy, int& starstroka, int& beforestar, char** starredact, int& nowstring) {
	if (index != 0) {
		index = ACTUALMENUPOSITION - 1;
		if (ACTUALMENUPOSITION % stringsymbols == 0) starstroka--;
		navigate(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
		ACTUALMENUPOSITION = index;
		beforestar = starstroka;
	}
}
void saveg(int countofsymbols, string* textredactor, char** starredact) {
	if (file_name[0] == '\0') {
		system("cls");
		cout << "Enter file name: "; 
		cin >> file_name;
	}
	ofstream fout(file_name);
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
string* increase(string* textredactor, int newSize)
{
	string* newArr = new string[newSize];
	delete[] textredactor;
	return newArr;
}
int main()
{
	string s;
	char temp;
	filechange(s,temp);
	
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
		if (i % stringsymbols == 0 && i != 0) {
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
		if (afterposition % stringsymbols == 0 && (beforeposition+1) % stringsymbols == 0) {
			nowstring++;
			posx = 40;
		}
		else posx++;
	}
	else if (afterposition < beforeposition) {
		if (beforeposition % stringsymbols == 0 && (afterposition+1) % stringsymbols == 0) {
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
	Sleep(300u);
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
			if (x == down) {
				if ((index + stringsymbols) < countofsymbols) {
					downg(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
				}
			}
			else if (x == up)
			{
				if (nowstring > 1 && index < countofsymbols) {
					upg(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
				}
			}
			else if (x == rightt)
			{
				if (index != (countofsymbols - 1)) {
					rightg(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
				}
			}
			else if (x == leftt)
			{
				leftg(ACTUALMENUPOSITION, index, posx, posy, starstroka, beforestar, starredact, nowstring);
			}
		}
		else if (x == save) {
			saveg(countofsymbols, textredactor, starredact);
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
				if (i % stringsymbols == 0 && i != 0) {
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
		else if (x == backspace && countofsymbols != 1) {
			system("cls");
			star = { posx, posy + 1 };
			SetConsoleCursorPosition(hOut, star);
			cout << "*";
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
				if (i % stringsymbols == 0 && i != 0) {
					pos.X = 40;
					pos.Y++;
					pos.Y++;
				}
				SetConsoleCursorPosition(hOut, pos);
				cout << textredactor[i];
				pos.X++;
			}
			/*i++;
			if (i % stringsymbols == 0 && i != 0) {
				pos.X = 40;
				pos.Y++;
				pos.Y++;
			}
			SetConsoleCursorPosition(hOut, pos);
			cout << " ";
			if ((countofsymbols+1) % 19 == 0 || ((countofsymbols+1) % stringsymbols) % 19 == 0) {
				int del = (countofsymbols+2) / stringsymbols;
				pos.Y = 10;
				pos.X = 60;
				SetConsoleCursorPosition(hOut, pos);
				cout << " ";
			}*/
		}
	}
}
