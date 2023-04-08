#include "ProgressBar.h"

#ifndef PROGRESSBAR_C
#define PROGRESSBAR_C

ProgressBar::ProgressBar(int max)
{
	this->length = 50;
	this->symbol = '>';
	this->max = max;
}

void ProgressBar::refresh(int progress)
{
	if((100*(progress+1))%max == 0)
	{
		int percent = 100*(progress+1)/(this->max);
		cout << "[" << flush;
		for(int i = 0; i < percent/(100/(this->length)); i++)
			cout << this->symbol << flush;
		for(int i = 0; i < (this->length)-percent/(100/(this->length)); i++)
			cout << " " << flush;

		cout << "] " << flush;
		cout << percent << "%";

		if(percent < 100)
		{
			if(percent < 10)
				cout << "\b\b" << flush;
			else if(percent < 100 && percent >= 10)
				cout << "\b\b\b" << flush;
		}

		if(percent < 100)
			cout << "\b\b" << flush;
		if(percent < 100)
			for(int i = 0; i < 50; i++)
				cout << "\b" << flush;

		if(percent < 100)
			cout << "\b" << flush;
	}	
}

void ProgressBar::setSymbol(char symbol)
{
	this->symbol = symbol;
}

void ProgressBar::setLength(int length)
{
	if(length <= 50 && length > 0)
		this->length = length;
	else
		cout << "zla wartosc length, length = 50" << endl;
}

#endif