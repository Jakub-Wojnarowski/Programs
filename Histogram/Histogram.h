#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>

using namespace std;

class Histogram
{
	private:
		int n;
		int nEntries;
		int nBins;
		double xMin;
		double xMax;
		double rowHeight;
		double maxValue;
		int height;
		const char* sign;
		double* binContent;
		double (*funkcja)(double);
	public:
		Histogram();
		~Histogram();
		void setnBins(int=50);
		void setheight(int=30);
		void setxMin(double=0);
		void setxMax(double=1);
		void setn(int=2);
		void setsign(const char*);
		void print();
		void getFunction(double (*)(double));
		void alocate();
};

#endif