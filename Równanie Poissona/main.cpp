#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

#define N 31
#define dx 1
#define d 4
#define x_0 4
#define IT 500

void wypisz(double**);

int main()
{
	cout.precision(1);

	fstream data;
	vector<double> a;
	double** u;
	double** a_d;
	u = new double* [2*N + 1];
	for (int i = 0; i < 2 * N + 1; i++)
		u[i] = new double[2*N + 1];

	double** RO;
	RO = new double* [2 * N + 1];
	for (int i = 0; i < 2 * N + 1; i++)
		RO[i] = new double[2 * N + 1];

	double** RO_p;
	RO_p = new double* [2 * N + 1];
	for (int i = 0; i < 2 * N + 1; i++)
		RO_p[i] = new double[2 * N + 1];

	//wybór trybu
	int tryb;
	do
	{
		cout << "1. relaksacja\n2. nadrelaksacja (OMEGA = 1.9)\n3. nadrelaksacja (OMEGA = 1.1)\n4. minimalizacja dzialania\n";
		cin >> tryb;
		system("cls");
	} while (tryb != 1 && tryb != 2 && tryb != 3 && tryb != 4);

	//zapis trybu
	data.open("tryb.txt", ios::out);
	data << tryb;
	data.close();

	double OMEGA;
	if (tryb == 2)
		OMEGA = 1.9;
	else if (tryb == 3)
		OMEGA = 1.1;

	//warunki pocz¹tkowe

	for (int i = 0; i < 2 * N + 1; i++)
		for (int j = 0; j < 2 * N + 1; j++)
		{
			int I = i - 31;
			int J = j - 31;
			if (I <= 15 && I >= -15 && J <= 15 && J >= -15)
				u[i][j] = 1;
			else
				u[i][j] = 0;
		}

	for (int i = 0; i < 2 * N + 1; i++)
		for (int j = 0; j < 2 * N + 1; j++)
		{
			double I = static_cast<double>(i) - 31;
			double J = static_cast<double>(j) - 31;
			if (i != 0 && j != 0 && i != 62 && j != 62)
				RO[i][j] = exp(-((J - x_0) * (J - x_0) + I * I) / (d * d)) - exp(-((J + x_0) * (J + x_0) + I * I) / (d * d));
			else
				RO[i][j] = 0;
		}

	//ustawiamy wartoœci brzegów u_p na wartoœci u i RO_p na RO 
	for (int i = 0; i < 2 * N + 1; i++)
		{
			RO_p[0][i] = RO[0][i];
			RO_p[62][i] = RO[62][i];
			RO_p[i][0] = RO[i][0];
			RO_p[i][62] = RO[i][62];
		}

	//iteracje
	for (int it = 0; it < IT; it++)
	{
		if (tryb == 1 || tryb == 2 || tryb == 3) //relaksacja (nadrelaksaacja)
		{
			//iterujemy u
			for (int i = 0; i < 2 * N + 1; i++)
				for (int j = 0; j < 2 * N + 1; j++)
					if (i != 0 && j != 0 && i != 62 && j != 62)
						if (tryb == 1)  //relaksacja
							u[i][j] = (u[i + 1][j] + u[i - 1][j] + u[i][j + 1] + u[i][j - 1] + RO[i][j] * dx * dx) / 4;
						else if (tryb == 2 || tryb == 3)  //nadrelaksacja
							u[i][j] = (1 - OMEGA) * u[i][j] + OMEGA * (u[i + 1][j] + u[i - 1][j] + u[i][j + 1] + u[i][j - 1] + RO[i][j] * dx * dx) / 4;

			//Obliczamy a
			double temp = 0;
			for (int i = 0; i < 2 * N + 1; i++)
				for (int j = 0; j < 2 * N + 1; j++)
					if (i != 0 && j != 0 && i != 62 && j != 62)
						temp -= (0.5 * u[i][j] * (u[i + 1][j] + u[i - 1][j] + u[i][j + 1] + u[i][j - 1] - 4 * u[i][j]) / (dx * dx) + RO[i][j] * u[i][j]) * dx * dx;
			a.push_back(temp);
		}
		else if (tryb == 4) //minimalizacja dzia³ania
		{
			static double a_l, a_ld;
			static double aa[4];
			static double dlt[4] = { 0.0, 0.5, 1.0 };
			static double dlt_min;
			static double a_min = 1000000; //jakaœ du¿a wartoœæ

			static double a_0;
			//wyliczamy a(0)
			if (it == 0)
			{
				a_0 = 0;
				for (int i = 0; i < 2 * N + 1; i++)
					for (int j = 0; j < 2 * N + 1; j++)
						if (i != 0 && j != 0 && i != 62 && j != 62)
							a_0 -= (0.5 * u[i][j] * (u[i + 1][j] + u[i - 1][j] + u[i][j + 1] + u[i][j - 1] - 4 * u[i][j]) / (dx * dx) + RO[i][j] * u[i][j]) * dx * dx;
			}

			//iterujemy a
			for (int i = 0; i < 2 * N + 1; i++)
				for (int j = 0; j < 2 * N + 1; j++)
					if (i != 0 && j != 0 && i != 62 && j != 62)
					{		
						for (int m = 0; m < 3; m++)  //wyznaczamy a ka¿dego delta 1, 2 i 3
						{
							a_l = 0, a_ld = 0;
							for (int k = i - 1; k <= i + 1; k++)
								for (int l = j - 1; l <= j + 1; l++)
									if (k != 0 && l != 0 && k != 62 && l != 62)
									{
										a_l -= (0.5 * u[k][l] * (u[k + 1][l] + u[k - 1][l] + u[k][l + 1] + u[k][l - 1] - 4 * u[k][l]) / (dx * dx) + RO[k][l] * u[k][l]) * dx * dx;
										u[i][j] += dlt[m];
										a_ld -= (0.5 * u[k][l] * (u[k + 1][l] + u[k - 1][l] + u[k][l + 1] + u[k][l - 1] - 4 * u[k][l]) / (dx * dx) + RO[k][l] * u[k][l]) * dx * dx;
										u[i][j] -= dlt[m];
									}
							aa[m] = a_0 - a_l + a_ld;
						}

						dlt[3] = 0.25 * (3 * aa[0] - 4 * aa[1] + aa[2]) / (aa[0] - 2 * aa[1] + aa[2]);  //wyliczamy delta 4
						a_l = 0, a_ld = 0;

						for (int k = i - 1; k <= i + 1; k++)  //wyznaczamy a dla delta 4
							for (int l = j - 1; l <= j + 1; l++)
								if (k != 0 && l != 0 && k != 62 && l != 62)
								{
									a_l -= (0.5 * u[k][l] * (u[k + 1][l] + u[k - 1][l] + u[k][l + 1] + u[k][l - 1] - 4 * u[k][l]) / (dx * dx) + RO[k][l] * u[k][l]) * dx * dx;
									u[i][j] += dlt[3];
									a_ld -= (0.5 * u[k][l] * (u[k + 1][l] + u[k - 1][l] + u[k][l + 1] + u[k][l - 1] - 4 * u[k][l]) / (dx * dx) + RO[k][l] * u[k][l]) * dx * dx;
									u[i][j] -= dlt[3];
								}
						aa[3] = a_0 - a_l + a_ld;

						for (int m = 0; m < 4; m++) //szukamy najmniejszego a i odpowiadaj¹cego mu delta
							if (aa[m] < a_min)
							{
								a_min = aa[m];
								dlt_min = dlt[m];
							}
						u[i][j] += dlt_min; 
						a_0 = a_min;
					}

			a.push_back(a_0);
		}

		// Zapis danych po 100 iteracjach
		if (it == 99)
		{
			for (int i = 0; i < 2 * N + 1; i++)
				for (int j = 0; j < 2 * N + 1; j++)
					if (i != 0 && j != 0 && i != 62 && j != 62)
							RO_p[i][j] = -(u[i + 1][j] + u[i - 1][j] + u[i][j - 1] + u[i][j + 1] - 4 * u[i][j]) / (dx * dx);
							
			data.open("u_100.txt", ios::out);
			for (int i = 0; i < 2 * N + 1; i++)
			{
				for (int j = 0; j < 2 * N + 1; j++)
					data << u[i][j] << " ";
				data << "\n";
			}
			data.close();

			data.open("RO_100.txt", ios::out);
			for (int i = 0; i < 2 * N + 1; i++)
			{
				for (int j = 0; j < 2 * N + 1; j++)
					data << RO_p[i][j] << " ";
				data << "\n";
			}
			data.close();

			data.open("delta_100.txt", ios::out);
			for (int i = 0; i < 2 * N + 1; i++)
			{
				for (int j = 0; j < 2 * N + 1; j++)
					data << RO_p[i][j] - RO[i][j] << " ";
				data << "\n";
			}
			data.close();

		}

	}
	
	//wypisz(u);

	//z ty³u tablicy a zapisujemy tryb programu
	a.push_back(tryb);

	//Zapis danych 500 iteracjach
	data.open("u_500.txt", ios::out);
	for (int i = 0; i < 2 * N + 1; i++)
	{
		for (int j = 0; j < 2 * N + 1; j++)
			data << u[i][j] << " ";
		data << "\n";
	}
	data.close();

	for (int i = 0; i < 2 * N + 1; i++)
		for (int j = 0; j < 2 * N + 1; j++)
			if (i != 0 && j != 0 && i != 62 && j != 62)
				RO_p[i][j] = -(u[i + 1][j] + u[i - 1][j] + u[i][j - 1] + u[i][j + 1] - 4 * u[i][j]) / (dx * dx);

	data.open("RO_500.txt", ios::out);
	for (int i = 0; i < 2 * N + 1; i++)
	{
		for (int j = 0; j < 2 * N + 1; j++)
			data << RO_p[i][j] << " ";
		data << "\n";
	}
	data.close();

	data.open("delta_500.txt", ios::out);
	for (int i = 0; i < 2 * N + 1; i++)
	{
		for (int j = 0; j < 2 * N + 1; j++)
			data << RO_p[i][j] - RO[i][j] << " ";
		data << "\n";
	}
	data.close();

	//zapis a dla ka¿dego z trybów z osobna
	if (tryb == 1)
	{
		data.open("a_1.txt", ios::out);
		for (int it = 0; it < IT + 1; it++)
			data << a[it] << " ";
		data.close();
	}
	else if (tryb == 2)
	{
		data.open("a_2.txt", ios::out);
		for (int it = 0; it < IT + 1; it++)
			data << a[it] << " ";
		data.close();
	}
	else if (tryb == 3)
	{
		data.open("a_3.txt", ios::out);
		for (int it = 0; it < IT + 1; it++)
			data << a[it] << " ";
		data.close();
	}
	else if (tryb == 4)
	{
		data.open("a_4.txt", ios::out);
		for (int it = 0; it < IT + 1; it++)
			data << a[it] << " ";
		data.close();
	}

	//zwalnianie pamiêci
	for (int i = 0; i < 2 * N + 1; i++)
		delete[] u[i];
	delete[] u;
}


//po wykoaniu obliczeñ w C++, po ka¿dym przypadku trzeba uruchomiæ skrypt w pythonie ¿eby narysowaæ wykresy 
//wykonanie obliczeñ dla nastêpnego przypadku nadpisuje pliki poprzedniego



void wypisz(double** u)
{
	for (int i = 0; i < 2 * N + 1; i++)
	{
		for (int j = 0; j < 2 * N + 1; j++)
			if (u[i][j] > 0.001 || u[i][j] < -0.001)
				cout << u[i][j] << " ";
			else
				cout << "0 ";
		cout << endl;
	}
}