﻿#include <iostream>
#include <string>
#include <cctype>
#include <climits>
#include <fstream>
#include <algorithm>
using namespace std;
void task1() 
{
	char text;
	string tolikoioioioi;
	for (int i = 0; i < INT_MAX; i++) 
	{
		cin >> text;
		if (text == '@') 
		{
			break;
		}
		else if (isdigit(text)) 
		{
		}
		else if (isupper(text)) 
		{
			tolikoioioioi += tolower(text);
		}
		else if (islower(text)) 
		{
			tolikoioioioi += toupper(text);
		}
	}
	cout << tolikoioioioi;
}

void task2() 
{
	double* mas = new double[10];
	int a = 10;
	double avarage;
	double sum = 0;
	int count = 0;
	for (int i = 0; i < 10; i++) 
	{
		cin >> mas[i];
		if (cin.fail()) 
		{
			a = i;
			break;
		}
	}
	for (int i = 0; i < a; i++) 
	{
		sum += mas[i];
	}
	avarage = sum / a;
	for (int i = 0; i < a; i++) 
	{
		if (mas[i] > avarage) count++;
	}
	cout << avarage << endl;
	cout << count;
	delete[] mas;
}

void task3() 
{
	string text;
	int size;
	int vowel = 0;
	int consonant = 0;
	int other = 0;
	string word;
	getline(cin, text);
	size = text.size();
	size++;
	for (int i = 0; i < size; i++) 
	{
		if (text[i] == ' ' || text[i] == '\0') 
		{
			if (word == "q") 
			{
				break;
			}
			if (word[0] == 'a' || word[0] == 'e' || word[0] == 'y' || word[0] == 'u' || word[0] == 'i' || word[0] == 'o') vowel++;
			else if (word[0] == 'q' || word[0] == 'w' || word[0] == 'r' || word[0] == 't' || word[0] == 'p' || word[0] == 's' || word[0] == 'd' || word[0] == 'f' ||
					word[0] == 'g' || word[0] == 'h' || word[0] == 'j' || word[0] == 'k' || word[0] == 'l' || word[0] == 'z' || word[0] == 'x' || word[0] == 'c' ||
					word[0] == 'v' || word[0] == 'b' || word[0] == 'n' || word[0] == 'm') consonant++;
			else other++;
			word.clear();
		}
		else 
		{
			word += text[i];
		}
	}
	cout << "vowel count = " << vowel << endl;
	cout << "consonant count = " << consonant << endl;
	cout << "other count = " << other;
}

void task4() 
{
	ifstream file;
	char buff;
	int count = 0;
	file.open("f:\\task4.txt");
	while (file >> buff) count++;
	cout << count;
	file.close();
}

double add(double x, double y) 
{
	return x + y;
}
double multiplication(double x, double y) 
{
	return x * y;
}
double maximum(double x, double y)
{
	 return max(x, y);
}
double calculate(double x, double y, double (*f)(double x, double y))
{
	return f(x, y);
}
void calculateArray(double x, double y, double (*ptrFunc[3])(double, double))
{
	double result;
	for (int i = 0; i < 3; i++)
	{
		result = ptrFunc[i](x, y);
		cout << result << endl;
	}
}
int main()
{
		//task1();
		//task2();
		//task3();
		//task4();
		//double k = calculate(2.5, 10., add);
		//cout << k;

		double (*ptrFunc[3])(double, double) = { add, multiplication, maximum };
		calculateArray(10, 5, ptrFunc);
	return 0;
}