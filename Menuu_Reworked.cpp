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
map <short, string> fourthmap;
void Button1();
void Button2();
void Button3();
void defaultt();
void peremeshenie(short index, short ACTUALMENUPOSITION, short posx, short posy, short variantofmap);
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
	else if (variantofmap == 3)
	{
		s = thirdmap.find(beforeposition)->second;
	}
	else 
	{
		s = fourthmap.find(beforeposition)->second;
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
	else if (variantofmap == 3)
	{
		news = thirdmap.find(afterposition)->second;
	}
	else
	{
		news = fourthmap.find(afterposition)->second;
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
void Button1() {
	int index;
	system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 40, 10 };
	vector <string> strs{ "*Punkt11*", " Punkt12 ", " Punkt13 " };
	for (string line : strs)
	{
		SetConsoleCursorPosition(hOut, pos);
		cout << line << endl;
		pos.Y++;
	}
	short ACTUALMENUPOSITION = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		secondmap.insert(pair<short, string>(i, strs[i]));
	}
	pos.Y = 10;
	peremeshenie(0, ACTUALMENUPOSITION, pos.X, pos.Y, 2);
}
void Button2() {
	int index;
	system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 40, 10 };
	vector <string> strs{ "*Punkt21*", " Punkt22 ", " Punkt23 " };
	for (string line : strs)
	{
		SetConsoleCursorPosition(hOut, pos);
		cout << line << endl;
		pos.Y++;
	}
	short ACTUALMENUPOSITION = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		thirdmap.insert(pair<short, string>(i, strs[i]));
	}
	pos.Y = 10;
	peremeshenie(0, ACTUALMENUPOSITION, pos.X, pos.Y, 3);
}
void Button3() {
	int index;
	system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {40, 10 };
	vector <string> strs{ "*Punkt31*", " Punkt32 ", " Punkt33 " };
	for (string line : strs)
	{
		SetConsoleCursorPosition(hOut, pos);
		cout << line << endl;
		pos.Y++;
	}
	short ACTUALMENUPOSITION = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		fourthmap.insert(pair<short, string>(i, strs[i]));
	}
	pos.Y = 10;
	peremeshenie(0, ACTUALMENUPOSITION, pos.X, pos.Y, 4);
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
		if(variantofmap == 2 || variantofmap == 3 || variantofmap == 4)
		defaultt();
	}
	else if (GetAsyncKeyState(VK_RETURN))
	{	
		if (variantofmap == 1) {
			if (posy == 10) Button1();
			if (posy == 11) Button2();
			if (posy == 12) Button3();
		}
	}
	}
}
void defaultt() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 40, 10 };
	vector <string> strs{ "*Button1*", " Button2 ", " Button3 " };
	for (string line : strs)
	{
		SetConsoleCursorPosition(hOut, pos);
		cout << line << endl;
		pos.Y++;
	}
	short ACTUALMENUPOSITION = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		mymap.insert(pair<short, string>(i, strs[i]));
	}
	pos.Y = 10;
	peremeshenie(0, ACTUALMENUPOSITION, pos.X, pos.Y, 1);
}
int main()
{
	defaultt();
}
