#include <iostream>


using namespace std;

#ifndef MATRIX_H
#define MATRIX_H

class matrix;
class complex;

class point1D
{
	protected:
		int x;
	public:
		point1D(int = 0);	
		~point1D();
		int getX();
		void setX(int);
		complex operator-(point1D);
};

class point2D : public point1D
{
	protected:
		int y;
	public:
		point2D(int = 0, int = 0);
		~point2D();
		int getY();
		void setXY(int, int);
		matrix operator-(point2D);
};

class point3D : public point2D
{
	protected:
		int z;
	public:
		point3D(int = 0, int = 0, int = 0);
		~point3D();
		int getZ();
		void setXYZ(int, int, int);
		matrix operator-(point3D);
};

class complex
{
	public:
		int r, i;
		complex(int = 0, int = 0);
		~complex();
		void display();
		set(int, int);
		complex operator+(const complex);
		complex operator-(const complex);
		complex operator*(const complex);
		operator+=(const complex);
		operator*();
};

class matrix 
{
	private:
		int y, x; // matrix A(liczba wierszy, liczba kolumn);
		complex** tab;
		complex getNumber(int, int);
		complex cgetNumber(int, int) const;
	public:
		matrix(int, int);
		matrix(const matrix&);
		~matrix();
		void fillMatrix(char = 'r');
		void changeSize(int, int);
		void displayMatrix();
		void setNumber(int, int, complex = 0);
		matrix operator+(const matrix);
		matrix operator-(const matrix);
		matrix operator*(const matrix);
		operator*();
		operator=(const matrix);
		matrix pow(const matrix, const unsigned int);
};


#endif
