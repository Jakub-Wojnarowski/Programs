#include <iostream>
#include <cmath>
#include <fstream>
#include "funkcje.h"


using namespace std;

int main()
{
	int tryb;
	do
	{
		cout << "Wybierz tryb:\n1) Metoda Eulera\n2) Metoda trapezow\n";
		cin >> tryb;
		cout << endl;
	} while (tryb != 1 && tryb != 2);


	int krok, tlumienie;
	double dt, alfa;
	do
	{
		cout << "Podaj krok czasowy:\n1) 0.01s\n2) 0.001s\n";
		cin >> krok;
		cout << endl;
	} while (krok != 1 && krok != 2);
	if (krok == 1)
		dt = 0.01;
	else if (krok == 2)
		dt = 0.001;

	do
	{
		cout << "Podaj wspolczynnik tlumienia:\n1) 0\n2) 0.5\n3) 5\n4) 201\n";
		cin >> tlumienie;
		cout << endl;
	} while (tlumienie != 1 && tlumienie != 2 && tlumienie != 3 && tlumienie != 4);
	if (tlumienie == 1)
		alfa = 0;
	if (tlumienie == 2)
		alfa = 0.5;
	else if (tlumienie == 3)
		alfa = 5;
	else if (tlumienie == 4)
		alfa = 201;

	if(tryb == 1)
		Euler(dt, alfa);
	else if(tryb == 2)
		trapez(dt, alfa);

}


