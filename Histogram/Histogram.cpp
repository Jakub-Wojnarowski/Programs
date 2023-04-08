#include "Histogram.h"

Histogram::Histogram()
{
	n = 2;
  nEntries = 1000;
  nBins = 50;
  xMin = 0;
  xMax = 1;
  height = 30;
	rowHeight = 0;
	maxValue = 0;
	binContent = NULL;
	funkcja = NULL;
	sign = "|";
}

Histogram::~Histogram()
{
	delete [] binContent;
}

void Histogram::setnBins(int nBins)
{
	this->nBins = nBins;
}

void Histogram::setheight(int height)
{
	this->height = height;
}

void Histogram::setxMin(double xMin)
{
	this->xMin = xMin;
}

void Histogram::setxMax(double xMax)
{
	this->xMax = xMax;
}

void Histogram::setn(int n)
{
	this->n = n;
}

void Histogram::setsign(const char* sign)
{
	this->sign = sign;
}

void Histogram::alocate()
{
	if(binContent != NULL)
		delete [] binContent;
	const double binWidth = (xMax-xMin)/nBins;
	int nBinsTotal = nBins+2;
	binContent = new double[nBinsTotal];
	for(int i=0; i<nBinsTotal; ++i)
  	binContent[i] = 0;
	
	//double vals[nEntries];
 // double sum = 0;

  for(int i=0; i<nEntries; ++i){
    double xi = 0;
    for(int j=0; j<n; ++j) xi += rand()/double(RAND_MAX);
    xi /= n;
    //vals[i] = xi;
    //sum += xi;

    int bin;
    if(xi<xMin) bin = 0;
    else if(xi>=xMax) bin=nBinsTotal-1;
    else bin = (xi-xMin)/binWidth+1;

    ++binContent[bin];
	}
	maxValue = 0;
  for(int val = 0; val < nBinsTotal; val++)
    if(binContent[val]>maxValue) maxValue = binContent[val];

  rowHeight = maxValue/height;
}

void Histogram::print()
{
	//if(funkcja == NULL)
//	{
		for(int i=height-1; i>=0; --i){
    	for(int j=0; j<nBins+2; ++j){
      	int binContentInRows = ((double)binContent[j]) / rowHeight;
      	std::cout << (binContentInRows>i?sign:" ");
    	}
    	std::cout << " " << maxValue*(i+1)/height << std::endl;
  	}
//	}
//	else
//	{

//	}
}

void Histogram::getFunction(double (*funkcja)(double x))
	{
	this->funkcja = funkcja;
	if(binContent != NULL)
		delete [] binContent;
	//const double binWidth = (xMax-xMin)/nBins;
	int nBinsTotal = nBins+2;
	binContent = new double[nBinsTotal];
	for(int i=0; i<nBinsTotal; ++i)
  	binContent[i] = 0;
	
	//double vals[nEntries];
 // double sum = 0;
/*
  for(int i=0; i<nEntries; ++i){
    double xi = 0;
    //for(int j=0; j<n; ++j) 
		xi += funkcja(rand()/double(RAND_MAX));
    //xi /= n;
    //vals[i] = xi;
    //sum += xi;


    int bin;
    if(xi<xMin) bin = 0;
    else if(xi>=xMax) bin=nBinsTotal-1;
    else bin = (xi-xMin)/binWidth+1;

    ++binContent[bin];
	}*/
	for(int i = 0; i < nBinsTotal; i++)
	{ 
		binContent[i] = (double)funkcja(xMin + i*(xMax-xMin)/nBinsTotal);
		cout << binContent[i] << " ";
	}
		cout << endl;
	maxValue = 0;
  for(int val = 0; val < nBinsTotal; val++)
    if(binContent[val]>maxValue) maxValue = binContent[val];

  rowHeight = maxValue/height;
	}