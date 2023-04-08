#include <iostream>
#include <cmath>
#include <fstream>
#include "funkcje.h"

#define m 1
#define v_0 0
#define x_0 2.8
#define dx 0.01

using namespace std;

void Euler(double dt, double alfa)
{
	fstream data;
	
	double* v = new double[30 / dt];
	double* x = new double[30 / dt];
	double* Ek = new double[30 / dt];
	double* Ve = new double[30 / dt];
	double* E = new double[30 / dt];

	v[0] = v_0;
	x[0] = x_0;
	Ek[0] = m * v[0] * v[0] / 2;
	Ve[0] = -exp(-pow(x[0], 2)) - 1.2 * exp(-pow(x[0] - 2, 2));
	E[0] = Ek[0] + Ve[0];

	for (int i = 0; i < 30 / dt - 1; i++)
	{
		v[i + 1] = v[i] - 1.0 / m * (-exp(-pow(x[i] + dx, 2)) - 1.2 * exp(-pow(x[i] + dx - 2, 2)) + exp(-pow(x[i] - dx, 2)) + 1.2 * exp(-pow(x[i] - dx - 2, 2))) / (2 * dx) * dt
			- alfa * v[i] * dt;
		x[i + 1] = x[i] + v[i] * dt;
		Ek[i + 1] = m * v[i + 1] * v[i + 1] / 2;
		Ve[i + 1] = -exp(-pow(x[i + 1], 2)) - 1.2 * exp(-pow(x[i + 1] - 2, 2));
		E[i + 1] = Ek[i + 1] + Ve[i + 1];
	}

	data.open("x.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << x[i] << " ";
	data.close();

	data.open("v.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << v[i] << " ";
	data.close();

	data.open("Ek.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << Ek[i] << " ";
	data.close();

	data.open("Ve.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << Ve[i] << " ";
	data.close();

	data.open("E.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << E[i] << " ";
	data.close();
	

	delete[] v;
	delete[] x;
	delete[] Ek;
	delete[] Ve;
	delete[] E;
}

void trapez(double dt, double alfa)
{
	fstream data;

	double* v = new double[30 / dt];
	double* x = new double[30 / dt];
	double* Ek = new double[30 / dt];
	double* Ve = new double[30 / dt];
	double* E = new double[30 / dt];

	v[0] = v_0;
	x[0] = x_0;
	Ek[0] = m * v[0] * v[0] / 2;
	Ve[0] = -exp(-pow(x[0], 2)) - 1.2 * exp(-pow(x[0] - 2, 2));
	E[0] = Ek[0] + Ve[0];

	for (int i = 0; i < 30 / dt - 1; i++)
	{
		double f1 = 100, f2 = 100;
		double d_x, d_v, d2V;
		x[i + 1] = x[i];
		v[i + 1] = v[i];

		if (i == 0)
			data.open("F.txt", ios::out);

		while (f1 > 0.000001 || f2 > 0.000001 || f1 < -0.000001 || f2 < -0.000001)
		{
			f1 = x[i + 1] - x[i] - v[i + 1] * dt / 2 - v[i] * dt / 2;
			f2 = v[i + 1] - v[i] - dt / 2 *	
				(-1.0 / m * (-exp(-pow(x[i + 1] + dx, 2)) - 1.2 * exp(-pow(x[i + 1] + dx - 2, 2)) + exp(-pow(x[i + 1] - dx, 2)) + 1.2 * exp(-pow(x[i + 1] - dx - 2, 2))) / (2 * dx) - alfa * v[i + 1]
				- 1.0 / m * (-exp(-pow(x[i] + dx, 2)) - 1.2 * exp(-pow(x[i] + dx - 2, 2)) + exp(-pow(x[i] - dx, 2)) + 1.2 * exp(-pow(x[i] - dx - 2, 2))) / (2 * dx) - alfa * v[i]);
			d2V = ( -exp(-pow(x[i + 1] + dx, 2)) - 1.2 * exp(-pow(x[i + 1] + dx - 2, 2)) 
				- exp(-pow(x[i + 1] - dx, 2)) - 1.2 * exp(-pow(x[i + 1] - dx - 2, 2)) 
				+ 2*(exp(-pow(x[i + 1], 2)) + 1.2 * exp(-pow(x[i + 1] - 2, 2))) )/ (dx * dx);

			d_x = -(1 + dt * alfa / 2) * f1 - dt / 2 * f2;
			d_v = -f2 + dt / (2 * m) * d2V * f1;

			x[i + 1] = x[i + 1] + d_x;
			v[i + 1] = v[i + 1] + d_v;

			if (i == 0)
				data << f1 << " " << f2 << "\n";

		}
		if (i == 0)
			data.close();

		Ek[i + 1] = m * v[i + 1] * v[i + 1] / 2;
		Ve[i + 1] = -exp(-pow(x[i + 1], 2)) - 1.2 * exp(-pow(x[i + 1] - 2, 2));
		E[i + 1] = Ek[i + 1] + Ve[i + 1];
	}


	data.open("x.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << x[i] << " ";
	data.close();

	data.open("v.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << v[i] << " ";
	data.close();

	data.open("Ek.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << Ek[i] << " ";
	data.close();

	data.open("Ve.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << Ve[i] << " ";
	data.close();

	data.open("E.txt", ios::out);
	for (int i = 0; i < 30 / dt; i++)
		data << E[i] << " ";
	data.close();

	delete[] v;
	delete[] x;
	delete[] Ek;
	delete[] Ve;
	delete[] E;
}
