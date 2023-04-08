#include <iostream>

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

using namespace std;

class ProgressBar
{
	private:
		char symbol;
		int max;
		int length;
	public:
		ProgressBar(int);
		void refresh(int);
		void setSymbol(char);
		void setLength(int);  // maksymalnie 50
};


#endif