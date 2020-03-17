#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <map>
#include <vector>
using namespace std;

map <short, string> mymap;
map <short, string> secondmap;
map <short, string> thirdmap;
void mansi(short& ACTUALMENUPOSITION, short& posx, short& posy);
void Button1();
void Button2();
void defaultt();
void navigate(short beforeposition, short afterposition, short& posx, short& posy, int variantofmap)
{
	string s;
	string news;
	if (variantofmap == 1)
	{
		s = mymap.find(beforeposition)->second;
	}
	else if(variantofmap == 2)
	{
		s = secondmap.find(beforeposition)->second;
	}
	else 
	{
		s = thirdmap.find(beforeposition)->second;
	}
	s[0] = ' '; s[s.size() - 1] = ' ';
	if (variantofmap == 1)
	{
		news = mymap.find(afterposition)->second;
	}
	else if (variantofmap == 2)
	{
		news = secondmap.find(afterposition)->second;
	}
	else
	{
		news = thirdmap.find(afterposition)->second;
	}
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



void fillmap(vector <string>& strs)
{
	for (int i = 0; i < strs.size(); i++)
	{
		mymap.insert(pair<short, string>(i, strs[i]));
	}
}

void mansi(short& ACTUALMENUPOSITION, short& posx, short& posy) {
	if (GetAsyncKeyState(VK_DOWN)) {
		if (ACTUALMENUPOSITION == 2)
		{
			navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION - 2, posx, posy, 1);
			ACTUALMENUPOSITION--;
			ACTUALMENUPOSITION--;
		}
		else
		{
			navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION + 1, posx, posy, 1);
			ACTUALMENUPOSITION++;
		}
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		if (ACTUALMENUPOSITION == 0)
		{
			navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION + 2, posx, posy, 1);
			ACTUALMENUPOSITION += 2;
		}
		else
		{
			navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION - 1, posx, posy, 1);
			ACTUALMENUPOSITION--;
		}
	}
	else if (GetAsyncKeyState(VK_RETURN))
	{
		if(posy==10) Button1();
		if (posy == 11) Button2();
	}
}
void Button1() {
	system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	short posx = 40;
	short posy = 10;
	COORD pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	string str1 = "*Oleg*";
	cout << str1 << endl;
	string str2 = " Drochila ";
	posy++;
	pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	cout << str2 << endl;
	vector <string> strs;
	strs.push_back(str1); strs.push_back(str2);
	short ACTUALMENUPOSITION = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		secondmap.insert(pair<short, string>(i, strs[i]));
	}
	posy = 10;
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN)) {
			if (ACTUALMENUPOSITION == 1)
			{
				navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION - 1, posx, posy, 2);
				ACTUALMENUPOSITION--;
			}
			else
			{
				navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION + 1, posx, posy, 2);
				ACTUALMENUPOSITION++;
			}
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			if (ACTUALMENUPOSITION == 0)
			{
				navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION + 1, posx, posy, 2);
				ACTUALMENUPOSITION += 1;
			}
			else
			{
				navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION - 1, posx, posy, 2);
				ACTUALMENUPOSITION--;
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {
			defaultt();
		}
	}
}
void Button2() {
	system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	short posx = 40;
	short posy = 10;
	COORD pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	string str1 = "*Eto*";
	cout << str1 << endl;
	string str2 = " Vtoroi ";
	posy++;
	pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	cout << str2 << endl;
	string str3 = " Punkt ";
	posy++;
	pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	cout << str3 << endl;
	vector <string> strs;
	strs.push_back(str1); strs.push_back(str2); strs.push_back(str3);
	short ACTUALMENUPOSITION = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		thirdmap.insert(pair<short, string>(i, strs[i]));
	}
	posy = 10;
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN)) {
			if (ACTUALMENUPOSITION == 2)
			{
				navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION - 2, posx, posy, 3);
				ACTUALMENUPOSITION--;
				ACTUALMENUPOSITION--;
			}
			else
			{
				navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION + 1, posx, posy, 3);
				ACTUALMENUPOSITION++;
			}
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			if (ACTUALMENUPOSITION == 0)
			{
				navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION + 2, posx, posy, 3);
				ACTUALMENUPOSITION += 2;
			}
			else
			{
				navigate(ACTUALMENUPOSITION, ACTUALMENUPOSITION - 1, posx, posy, 3);
				ACTUALMENUPOSITION--;
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {
			defaultt();
		}
	}
}
void defaultt() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	short posx = 40;
	short posy = 10;
	COORD pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	string str1 = "*Button1*";
	cout << str1 << endl;
	string str2 = " Button2 ";
	posy++;
	pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	cout << str2 << endl;
	string str3 = " Button3 ";
	posy++;
	pos = { posx, posy };
	SetConsoleCursorPosition(hOut, pos);
	cout << str3 << endl;
	vector <string> strs;
	strs.push_back(str1); strs.push_back(str2); strs.push_back(str3);
	short ACTUALMENUPOSITION = 0;
	fillmap(strs);
	posy = 10;
	while (true)
	{
		mansi(ACTUALMENUPOSITION, posx, posy);
	}
}
int main()
{
	defaultt();
}
