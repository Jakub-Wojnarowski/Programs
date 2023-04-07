#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#define RAND_MAX 1000000;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

int start;

void wypelnij_0(char**);
void wypelnij_0(bool**);
void wypisz(char**, bool**);
void los(char**, bool**);
char int_to_char(int);
bool check(int, int, int, char**);
bool check_coord(int*, bool**);
void input(char**, bool**);
bool verify(char**);



int main()
{
	srand(time(NULL));
	char** tab = new char* [9];
	for (int i = 0; i < 9; i++)
		*(tab + i) = new char[9];

	bool** lock = new bool* [9];
	for (int i = 0; i < 9; i++)
		*(lock + i) = new bool[9];

	do
	{
		cout << "Wybierz poziom trudnoœci (od 1 do 3) : " << endl;
		cin >> start;
		system("cls");
	} while (start < 0 && start > 3);

	switch (start)
	{
		case 1:
			start = 40;
			break;
		case 2:
			start = 30;
			break;
		case 3:
			start = 20;
			break;
	}

	wypelnij_0(tab);
	wypelnij_0(lock);
	los(tab, lock);

	while (!verify(tab))
	{
		system("cls");
		wypisz(tab, lock);
		input(tab, lock);
	}

	system("cls");
	wypisz(tab, lock);
	cout << "You win !!!!!" << endl;

	for (int i = 0; i < 9; i++)
		delete [] *(tab + i);
	delete [] tab;

	for (int i = 0; i < 9; i++)
		delete[] * (lock + i);
	delete[] lock;
}

void wypelnij_0(char** tab)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			*(*(tab + i) + j) = '0';
}

void wypelnij_0(bool** lock)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			*(*(lock + i) + j) = 0;
}

void wypisz(char** tab, bool** lock)
{
	for (int i = 0; i < 9; i++)
	{
		cout << " ";
		if (i > 0 && i % 3 == 0)
			cout << "---------------------" << endl << " ";
		for (int j = 0; j < 9; j++)
		{
			if (j > 0 && j % 3 == 0)
				cout << "| ";

			if (*(*(tab + i) + j) == '0')
				cout << "  ";
			else
			{
				if (*(*(lock + i) + j) == 1)
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
				cout << *(*(tab + i) + j) << " ";
				if (*(*(lock + i) + j) == 1)
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}
		cout << endl;
	}
}

void los(char** tab, bool** lock)
{
	int N;
	int coord[2];
	for (int i = 0; i < start; i++)
	{
		do
		{
			coord[0] = (rand() % 9) + 1;
			coord[1] = (rand() % 9) + 1;
		} while (check_coord(coord, lock) == 0);

		do
		{
			N = (rand() % 9) + 1;
		} while (check(N, coord[0], coord[1], tab) == 0);
		*(*(lock + (coord[1] - 1)) + (coord[0] - 1)) = 1;
		*(*(tab + (coord[1] - 1)) + (coord[0] - 1)) = int_to_char(N);
	}
}

char int_to_char(int n)
{
	if (n == 1)
		return '1';
	else if (n == 2)
		return '2';
	else if (n == 3)
		return '3';
	else if (n == 4)
		return '4';
	else if (n == 5)
		return '5';
	else if (n == 6)
		return '6';
	else if (n == 7)
		return '7';
	else if (n == 8)
		return '8';
	else if (n == 9)
		return '9';
	else
		return '0';
}

bool check(int n, int x, int y, char** tab)
{
	//*(*(tab + (y - 1)) + (x - 1)) = int_to_char(n);
	char N = int_to_char(n);
	bool temp = 1;
	for (int i = 0; i < 9; i++)
	{
		if (i != x - 1)
			if (N == *(*(tab + (y - 1)) + i))
				temp = 0;
		if (i != y - 1)
			if (N == *(*(tab + i) + (x - 1)))
				temp = 0;
	}

	for (int i = (y - 1) - ((y - 1) % 3); i < (y - 1) + 3 - ((y - 1) % 3); i++)
		for (int j = (x - 1) - ((x - 1) % 3); j < (x - 1) + 3 - ((x - 1) % 3); j++)
			if (i != y - 1 && j != x - 1)
				if (N == *(*(tab + i) + j))
					temp = 0;

	return temp;
}

bool check_coord(int* coord, bool** lock)
{
	if (*(*(lock + *(coord + 1) - 1) + *coord - 1) == 1)
		return 0;
	else
		return 1;
}

void input(char** tab, bool** lock)
{
	int n;
	int coord[2];
	do
	{
		cout << "Wpisz x i y : " << endl;
		cin >> coord[0] >> coord[1];
		system("cls");
		wypisz(tab, lock);
	} while (!check_coord(coord, lock) && (coord[0] >= 1 && coord[0] <= 9) && (coord[1] >= 1 && coord[1] <= 9));

	do
	{
		cout << "Wpisz wartosc : " << endl;
		cin >> n;
		system("cls");
		wypisz(tab, lock);
	} while (!check(n, coord[0], coord[1], tab) && (n >= 1 && n <= 9));
	*(*(tab + (coord[1] - 1)) + (coord[0] - 1)) = int_to_char(n);
}

bool verify(char** tab)
{
	bool temp = 1;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (*(*(tab + i) + j) == '0')
				temp = 0;
	return temp;
}