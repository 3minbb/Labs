#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <map>
#include <vector>
using namespace std;
string button1 = "Button1";
string button2 = "Button2";
string button3 = "Button3";
string button4 = "Button4";
map <short, string> mymap;
map <short, string> secondmap;
map <short, string> thirdmap;
map <short, string> fourthmap;
void Buttons(string variantofbutton);
void defaultt();
void peremeshenie(short index, short ACTUALMENUPOSITION, short posx, short posy, string variantofmap);
void navigate(short beforeposition, short afterposition, short& posx, short& posy, string variantofmap)
{
	string s;
	string news;
	if (variantofmap == "Button1")
	{
		s = mymap.find(beforeposition)->second;
	}
	else if (variantofmap == "Button2")
	{
		s = secondmap.find(beforeposition)->second;
	}
	else if (variantofmap == "Button3")
	{
		s = thirdmap.find(beforeposition)->second;
	}
	else
	{
		s = fourthmap.find(beforeposition)->second;
	}
	s[0] = ' '; s[s.size() - 1] = ' ';
	if (variantofmap == "Button1")
	{
		news = mymap.find(afterposition)->second;
	}
	else if (variantofmap == "Button2")
	{
		news = secondmap.find(afterposition)->second;
	}
	else if (variantofmap == "Button3")
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
void Buttons(string variantofbutton) {
	int index;
	system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 40, 10 };
	vector <string> strs{ "*Punkt11*", " Punkt12 ", " Punkt13 " };
	vector <string> strs2{ "*Punkt21*", " Punkt22 ", " Punkt23 " };
	vector <string> strs3{ "*Punkt31*", " Punkt32 ", " Punkt33 " };
	if (variantofbutton == "Button2") {
		for (string line : strs)
		{
			SetConsoleCursorPosition(hOut, pos);
			cout << line << endl;
			pos.Y++;
		}
	}
	else if (variantofbutton == "Button3") {
		for (string line : strs2)
		{
			SetConsoleCursorPosition(hOut, pos);
			cout << line << endl;
			pos.Y++;
		}
	}
	else {
		for (string line : strs3)
		{
			SetConsoleCursorPosition(hOut, pos);
			cout << line << endl;
			pos.Y++;
		}
	}
	short ACTUALMENUPOSITION = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		if (variantofbutton == "Button2") secondmap.insert(pair<short, string>(i, strs[i]));
		else if (variantofbutton == "Button3") thirdmap.insert(pair<short, string>(i, strs2[i]));
		else fourthmap.insert(pair<short, string>(i, strs3[i]));
	}
	pos.Y = 10;
	peremeshenie(0, ACTUALMENUPOSITION, pos.X, pos.Y, variantofbutton);
}
void peremeshenie(short index, short ACTUALMENUPOSITION, short posx, short posy, string variantofmap) {
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
			if (variantofmap == "Button2" || variantofmap == "Button3" || variantofmap == "Button4")
				defaultt();
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (variantofmap == "Button1") {
				if (posy == 10) Buttons(button2);
				if (posy == 11) Buttons(button3);
				if (posy == 12) Buttons(button4);
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
	peremeshenie(0, ACTUALMENUPOSITION, pos.X, pos.Y, "Button1");
}
int main()
{
	defaultt();
}
