#include<iostream>
#include<math.h>
#include<fstream>
#include<vector>

using namespace std;

#define G 6.6741e-11
#define M 1.989e30
#define au 149597870700
#define PI 3.141592653

int main()
{
	int tryb;
	do
	{
		cout << "Wybierz metode:\n1) Euler\n2) RK4\n";
		cin >> tryb;
	} while (tryb != 1 && tryb != 2);

	int krok;
	do
	{
		cout << "Wybierz krok czasowy:\n1) Staly\n2) Automatyczny\n";
		cin >> krok;
	} while (krok != 1 && krok != 2);

	double tol;

	if (krok == 2)
	{
		int tol_c;
		do
		{
			cout << "Wybierz dokladnosc:\n1) 1000\n2) 100\n";
			cin >> tol_c;
			if (tol_c == 1)
				tol = 1000;
			else if (tol_c == 2)
				tol = 100;
		} while (tol_c != 1 && tol_c != 2);
	}
	else
		tol = 1000;


	fstream f;
	
	if (tryb == 1)
	{
		if (krok == 1)
		{
			double dt = 3600;
			double t = 13e9;
			int size = int(t / dt);

			double* x = new double[size];
			double* y = new double[size];
			double* r = new double[size];
			double* vx = new double[size];
			double* vy = new double[size];

			x[0] = 0;
			y[0] = 0.586 * au;
			r[0] = sqrt(pow(x[0], 2) + pow(y[0], 2));
			vx[0] = 54600;
			vy[0] = 0;

			for (int i = 0; i < size - 1; i++)
			{
				x[i + 1] = x[i] + vx[i] * dt;
				y[i + 1] = y[i] + vy[i] * dt;
				r[i + 1] = sqrt(pow(x[i + 1], 2) + pow(y[i + 1], 2));
				vx[i + 1] = vx[i] - G * M / pow(r[i], 3) * x[i] * dt;
				vy[i + 1] = vy[i] - G * M / pow(r[i], 3) * y[i] * dt;
			}

			f.open("x.txt", ios::out);
			for (int i = 0; i < size; i++)
				f << x[i] << " ";
			f.close();
			f.open("y.txt", ios::out);
			for (int i = 0; i < size; i++)
				f << y[i] << " ";
			f.close();
			f.open("tryb.txt", ios::out);
			f << tryb << " " << krok << " ";
			f.close();
			f.open("t.txt", ios::out);
			f << t << " ";
			f.close();

			delete[] x;
			delete[] y;
			delete[] r;
			delete[] vx;
			delete[] vy;
		}
		else if (krok == 2)
		{
			double dt = 600;
			double t = 13e9;
			double t_temp = 0;

			vector<double> x{ 0 };
			vector<double> y{ 0.586 * au };
			vector<double> r{ sqrt(pow(x[0], 2) + pow(y[0], 2)) };
			vector<double> vx{ 54600 };
			vector<double> vy{ 0 };
			vector<double> tm{ 0 };

			double ex, ey, e;
			double x_temp, x_p1, x_p2;
			double y_temp, y_p1, y_p2;
			double vx_temp, vx_p1, vx_p2;
			double vy_temp, vy_p1, vy_p2;
			double r_temp, r_p1, r_p2;

			while (t_temp <= t)
			{
				x_temp = x[x.size() - 1] + vx[vx.size() - 1] * dt;
				y_temp = y[y.size() - 1] + vy[vy.size() - 1] * dt;
				vx_temp = vx[vx.size() - 1] - G * M / pow(r[r.size() - 1], 3) * x[x.size() - 1] * dt;
				vy_temp = vy[vy.size() - 1] - G * M / pow(r[r.size() - 1], 3) * y[y.size() - 1] * dt;
				r_temp = sqrt(pow(x_temp, 2) + pow(y_temp, 2));

				x_p1 = x[x.size() - 1] + vx[vx.size() - 1] * dt / 2;
				y_p1 = y[y.size() - 1] + vy[vy.size() - 1] * dt / 2;
				vx_p1 = vx[vx.size() - 1] - G * M / pow(r[r.size() - 1], 3) * x[x.size() - 1] * dt / 2;
				vy_p1 = vy[vy.size() - 1] - G * M / pow(r[r.size() - 1], 3) * y[y.size() - 1] * dt / 2;
				r_p1 = sqrt(pow(x_p1, 2) + pow(y_p1, 2));

				x_p2 = x_p1 + vx_p1 * dt / 2;
				y_p2 = y_p1 + vy_p1 * dt / 2;
				vx_p2 = vx_p1 - G * M / pow(r_p1, 3) * x_p1 * dt / 2;
				vy_p2 = vy_p1 - G * M / pow(r_p1, 3) * y_p1 * dt / 2;
				r_p2 = sqrt(pow(x_p2, 2) + pow(y_p2, 2));

				ex = (x_p2 - x_temp);
				ey = (y_p2 - y_temp);
				if (abs(ex) > abs(ey))
					e = abs(ex);
				else
					e = abs(ey);

				if (e <= tol)
				{
					t_temp += dt;
					x.push_back(x_p2);
					y.push_back(y_p2);
					vx.push_back(vx_p2);
					vy.push_back(vy_p2);
					r.push_back(r_p2);
					tm.push_back(t_temp);
				}
				dt = 0.9 * dt * pow(tol / e, 1.0 / 2);
			}
			f.open("x.txt", ios::out);
			for (int i = 0; i < x.size(); i++)
				f << x[i] << " ";
			f.close();
			f.open("y.txt", ios::out);
			for (int i = 0; i < y.size(); i++)
				f << y[i] << " ";
			f.close();
			f.open("tryb.txt", ios::out);
			f << tryb << " " << krok << " " << tol << " ";
			f.close();
			f.open("t.txt", ios::out);
			for (int i = 0; i < tm.size(); i++)
				f << tm[i] << " ";
			f.close();
		}
	}
	else if (tryb == 2)
	{
		double uk[4];
		double kx[4];
		double ky[4];
		double kvx[4];
		double kvy[4];

		if (krok == 1)
		{
			double dt = 3600;
			double t = 13e9;
			int size = int(t / dt);

			double* x = new double[size];
			double* y = new double[size];
			double* r = new double[size];
			double* vx = new double[size];
			double* vy = new double[size];

			x[0] = 0;
			y[0] = 0.586 * au;
			r[0] = sqrt(pow(x[0], 2) + pow(y[0], 2));
			vx[0] = 54600;
			vy[0] = 0;

			for (int i = 1; i < size; i++)
			{
				uk[0] = x[i - 1];
				uk[1] = y[i - 1];
				uk[2] = vx[i - 1];
				uk[3] = vy[i - 1];

				kx[0] = uk[2];
				ky[0] = uk[3];
				kvx[0] = -G * M / pow(sqrt(pow(uk[0], 2) + pow(uk[1], 2)), 3) * uk[0];
				kvy[0] = -G * M / pow(sqrt(pow(uk[0], 2) + pow(uk[1], 2)), 3) * uk[1];;

				kx[1] = uk[2] + kvx[0] * dt / 2;
				ky[1] = uk[3] + kvy[0] * dt / 2;
				kvx[1] = -G * M / pow(sqrt(pow(uk[0] + kx[0] * dt / 2, 2) + pow(uk[1] + ky[0] * dt / 2, 2)), 3) * (uk[0] + kx[0] * dt / 2);
				kvy[1] = -G * M / pow(sqrt(pow(uk[0] + kx[0] * dt / 2, 2) + pow(uk[1] + ky[0] * dt / 2, 2)), 3) * (uk[1] + ky[0] * dt / 2);

				kx[2] = uk[2] + kvx[1] * dt / 2;
				ky[2] = uk[3] + kvy[1] * dt / 2;
				kvx[2] = -G * M / pow(sqrt(pow(uk[0] + kx[1] * dt / 2, 2) + pow(uk[1] + ky[1] * dt / 2, 2)), 3) * (uk[0] + kx[1] * dt / 2);
				kvy[2] = -G * M / pow(sqrt(pow(uk[0] + kx[1] * dt / 2, 2) + pow(uk[1] + ky[1] * dt / 2, 2)), 3) * (uk[1] + ky[1] * dt / 2);

				kx[3] = uk[2] + kvx[2] * dt;
				ky[3] = uk[3] + kvy[2] * dt;
				kvx[3] = -G * M / pow(sqrt(pow(uk[0] + kx[2] * dt, 2) + pow(uk[1] + ky[2] * dt, 2)), 3) * (uk[0] + kx[2] * dt);
				kvy[3] = -G * M / pow(sqrt(pow(uk[0] + kx[2] * dt, 2) + pow(uk[1] + ky[2] * dt, 2)), 3) * (uk[1] + ky[2] * dt);

				x[i] = x[i - 1] + dt / 6 * (kx[0] + 2 * kx[1] + 2 * kx[2] + kx[3]);
				y[i] = y[i - 1] + dt / 6 * (ky[0] + 2 * ky[1] + 2 * ky[2] + ky[3]);
				vx[i] = vx[i - 1] + dt / 6 * (kvx[0] + 2 * kvx[1] + 2 * kvx[2] + kvx[3]);
				vy[i] = vy[i - 1] + dt / 6 * (kvy[0] + 2 * kvy[1] + 2 * kvy[2] + kvy[3]);
			}

			f.open("x.txt", ios::out);
			for (int i = 0; i < size; i++)
				f << x[i] << " ";
			f.close();
			f.open("y.txt", ios::out);
			for (int i = 0; i < size; i++)
				f << y[i] << " ";
			f.close();
			f.open("tryb.txt", ios::out);
			f << tryb << " " << krok << " ";
			f.close();
			f.open("t.txt", ios::out);
			f << t << " ";
			f.close();

			delete[] x;
			delete[] y;
			delete[] r;
			delete[] vx;
			delete[] vy;
		}
		else if (krok == 2)
		{
			double dt = 600;
			double t = 13e9;
			double t_temp = 0;

			vector<double> x{ 0 };
			vector<double> y{ 0.586 * au };
			vector<double> r{ sqrt(pow(x[0], 2) + pow(y[0], 2)) };
			vector<double> vx{ 54600 };
			vector<double> vy{ 0 };
			vector<double> tm{ 0 };

			double ex, ey, e;
			double x_temp, x_p1, x_p2;
			double y_temp, y_p1, y_p2;
			double vx_temp, vx_p1, vx_p2;
			double vy_temp, vy_p1, vy_p2;
			double r_temp, r_p1, r_p2;

			double kx_p1[4], ky_p1[4], kvx_p1[4], kvy_p1[4];
			double kx_p2[4], ky_p2[4], kvx_p2[4], kvy_p2[4];

			while (t_temp <= t)
			{
				uk[0] = x[x.size() - 1];
				uk[1] = y[y.size() - 1];
				uk[2] = vx[vx.size() - 1];
				uk[3] = vy[vy.size() - 1];

				kx[0] = uk[2];
				ky[0] = uk[3];
				kvx[0] = -G * M / pow(sqrt(pow(uk[0], 2) + pow(uk[1], 2)), 3) * uk[0];
				kvy[0] = -G * M / pow(sqrt(pow(uk[0], 2) + pow(uk[1], 2)), 3) * uk[1];;

				kx[1] = uk[2] + kvx[0] * dt / 2;
				ky[1] = uk[3] + kvy[0] * dt / 2;
				kvx[1] = -G * M / pow(sqrt(pow(uk[0] + kx[0] * dt / 2, 2) + pow(uk[1] + ky[0] * dt / 2, 2)), 3) * (uk[0] + kx[0] * dt / 2);
				kvy[1] = -G * M / pow(sqrt(pow(uk[0] + kx[0] * dt / 2, 2) + pow(uk[1] + ky[0] * dt / 2, 2)), 3) * (uk[1] + ky[0] * dt / 2);

				kx[2] = uk[2] + kvx[1] * dt / 2;
				ky[2] = uk[3] + kvy[1] * dt / 2;
				kvx[2] = -G * M / pow(sqrt(pow(uk[0] + kx[1] * dt / 2, 2) + pow(uk[1] + ky[1] * dt / 2, 2)), 3) * (uk[0] + kx[1] * dt / 2);
				kvy[2] = -G * M / pow(sqrt(pow(uk[0] + kx[1] * dt / 2, 2) + pow(uk[1] + ky[1] * dt / 2, 2)), 3) * (uk[1] + ky[1] * dt / 2);

				kx[3] = uk[2] + kvx[2] * dt;
				ky[3] = uk[3] + kvy[2] * dt;
				kvx[3] = -G * M / pow(sqrt(pow(uk[0] + kx[2] * dt, 2) + pow(uk[1] + ky[2] * dt, 2)), 3) * (uk[0] + kx[2] * dt);
				kvy[3] = -G * M / pow(sqrt(pow(uk[0] + kx[2] * dt, 2) + pow(uk[1] + ky[2] * dt, 2)), 3) * (uk[1] + ky[2] * dt);

				x_temp = x[x.size()-1] + dt / 6 * (kx[0] + 2 * kx[1] + 2 * kx[2] + kx[3]);
				y_temp = y[y.size()-1] + dt / 6 * (ky[0] + 2 * ky[1] + 2 * ky[2] + ky[3]);
				vx_temp = vx[vx.size() - 1] + dt / 6 * (kvx[0] + 2 * kvx[1] + 2 * kvx[2] + kvx[3]);
				vy_temp = vy[vy.size() - 1] + dt / 6 * (kvy[0] + 2 * kvy[1] + 2 * kvy[2] + kvy[3]);


				kx_p1[0] = uk[2];
				ky_p1[0] = uk[3];
				kvx_p1[0] = -G * M / pow(sqrt(pow(uk[0], 2) + pow(uk[1], 2)), 3) * uk[0];
				kvy_p1[0] = -G * M / pow(sqrt(pow(uk[0], 2) + pow(uk[1], 2)), 3) * uk[1];;

				kx_p1[1] = uk[2] + kvx_p1[0] * dt / 4;
				ky_p1[1] = uk[3] + kvy_p1[0] * dt / 4;
				kvx_p1[1] = -G * M / pow(sqrt(pow(uk[0] + kx_p1[0] * dt / 4, 2) + pow(uk[1] + ky_p1[0] * dt / 4, 2)), 3) * (uk[0] + kx_p1[0] * dt / 4);
				kvy_p1[1] = -G * M / pow(sqrt(pow(uk[0] + kx_p1[0] * dt / 4, 2) + pow(uk[1] + ky_p1[0] * dt / 4, 2)), 3) * (uk[1] + ky_p1[0] * dt / 4);

				kx_p1[2] = uk[2] + kvx_p1[1] * dt / 4;
				ky_p1[2] = uk[3] + kvy_p1[1] * dt / 4;
				kvx_p1[2] = -G * M / pow(sqrt(pow(uk[0] + kx_p1[1] * dt / 4, 2) + pow(uk[1] + ky_p1[1] * dt / 4, 2)), 3) * (uk[0] + kx_p1[1] * dt / 4);
				kvy_p1[2] = -G * M / pow(sqrt(pow(uk[0] + kx_p1[1] * dt / 4, 2) + pow(uk[1] + ky_p1[1] * dt / 4, 2)), 3) * (uk[1] + ky_p1[1] * dt / 4);

				kx_p1[3] = uk[2] + kvx_p1[2] * dt/2;
				ky_p1[3] = uk[3] + kvy_p1[2] * dt/2;
				kvx_p1[3] = -G * M / pow(sqrt(pow(uk[0] + kx_p1[2] * dt/2, 2) + pow(uk[1] + ky_p1[2] * dt/2, 2)), 3) * (uk[0] + kx_p1[2] * dt/2);
				kvy_p1[3] = -G * M / pow(sqrt(pow(uk[0] + kx_p1[2] * dt/2, 2) + pow(uk[1] + ky_p1[2] * dt/2, 2)), 3) * (uk[1] + ky_p1[2] * dt/2);

				x_p1 = x[x.size() - 1] + dt / 12 * (kx_p1[0] + 2 * kx_p1[1] + 2 * kx_p1[2] + kx_p1[3]);
				y_p1 = y[y.size() - 1] + dt / 12 * (ky_p1[0] + 2 * ky_p1[1] + 2 * ky_p1[2] + ky_p1[3]);
				vx_p1 = vx[vx.size() - 1] + dt / 12 * (kvx_p1[0] + 2 * kvx_p1[1] + 2 * kvx_p1[2] + kvx_p1[3]);
				vy_p1 = vy[vy.size() - 1] + dt / 12 * (kvy_p1[0] + 2 * kvy_p1[1] + 2 * kvy_p1[2] + kvy_p1[3]);


				uk[0] = x_p1;
				uk[1] = y_p1;
				uk[2] = vx_p1;
				uk[3] = vy_p1;

				kx_p2[0] = uk[2];
				ky_p2[0] = uk[3];
				kvx_p2[0] = -G * M / pow(sqrt(pow(uk[0], 2) + pow(uk[1], 2)), 3) * uk[0];
				kvy_p2[0] = -G * M / pow(sqrt(pow(uk[0], 2) + pow(uk[1], 2)), 3) * uk[1];;

				kx_p2[1] = uk[2] + kvx_p2[0] * dt / 4;
				ky_p2[1] = uk[3] + kvy_p2[0] * dt / 4;
				kvx_p2[1] = -G * M / pow(sqrt(pow(uk[0] + kx_p2[0] * dt / 4, 2) + pow(uk[1] + ky_p2[0] * dt / 4, 2)), 3) * (uk[0] + kx_p2[0] * dt / 4);
				kvy_p2[1] = -G * M / pow(sqrt(pow(uk[0] + kx_p2[0] * dt / 4, 2) + pow(uk[1] + ky_p2[0] * dt / 4, 2)), 3) * (uk[1] + ky_p2[0] * dt / 4);

				kx_p2[2] = uk[2] + kvx_p2[1] * dt / 4;
				ky_p2[2] = uk[3] + kvy_p2[1] * dt / 4;
				kvx_p2[2] = -G * M / pow(sqrt(pow(uk[0] + kx_p2[1] * dt / 4, 2) + pow(uk[1] + ky_p2[1] * dt / 4, 2)), 3) * (uk[0] + kx_p2[1] * dt / 4);
				kvy_p2[2] = -G * M / pow(sqrt(pow(uk[0] + kx_p2[1] * dt / 4, 2) + pow(uk[1] + ky_p2[1] * dt / 4, 2)), 3) * (uk[1] + ky_p2[1] * dt / 4);

				kx_p2[3] = uk[2] + kvx_p2[2] * dt / 2;
				ky_p2[3] = uk[3] + kvy_p2[2] * dt / 2;
				kvx_p2[3] = -G * M / pow(sqrt(pow(uk[0] + kx_p2[2] * dt / 2, 2) + pow(uk[1] + ky_p2[2] * dt / 2, 2)), 3) * (uk[0] + kx_p2[2] * dt / 2);
				kvy_p2[3] = -G * M / pow(sqrt(pow(uk[0] + kx_p2[2] * dt / 2, 2) + pow(uk[1] + ky_p2[2] * dt / 2, 2)), 3) * (uk[1] + ky_p2[2] * dt / 2);

				x_p2 = x_p1 + dt / 12 * (kx_p2[0] + 2 * kx_p2[1] + 2 * kx_p2[2] + kx_p2[3]);
				y_p2 = y_p1 + dt / 12 * (ky_p2[0] + 2 * ky_p2[1] + 2 * ky_p2[2] + ky_p2[3]);
				vx_p2 = vx_p1 + dt / 12 * (kvx_p2[0] + 2 * kvx_p2[1] + 2 * kvx_p2[2] + kvx_p2[3]);
				vy_p2 = vy_p1 + dt / 12 * (kvy_p2[0] + 2 * kvy_p2[1] + 2 * kvy_p2[2] + kvy_p2[3]);


				ex = (x_p2 - x_temp)/15;
				ey = (y_p2 - y_temp)/15;
				if (abs(ex) > abs(ey))
					e = abs(ex);
				else
					e = abs(ey);

				if (e <= tol)
				{
					t_temp += dt;
					x.push_back(x_p2);
					y.push_back(y_p2);
					vx.push_back(vx_p2);
					vy.push_back(vy_p2);
					r.push_back(r_p2);
					tm.push_back(t_temp);
				}
				dt = 0.9 * dt * pow(tol / e, 1.0 / 5);
			}
			f.open("x.txt", ios::out);
			for (int i = 0; i < x.size(); i++)
				f << x[i] << " ";
			f.close();
			f.open("y.txt", ios::out);
			for (int i = 0; i < y.size(); i++)
				f << y[i] << " ";
			f.close();
			f.open("tryb.txt", ios::out);
			f << tryb << " " << krok << " " << tol << " ";
			f.close();
			f.open("t.txt", ios::out);
			for (int i = 0; i < tm.size(); i++)
				f << tm[i] << " ";
			f.close();
		}
	}
}
