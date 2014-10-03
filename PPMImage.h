//
//  PPMImage.h
//  
//
//  Created by Rhys Jordan Davies on 27/09/2014.
//
//

#ifndef ____PPMImage__
#define ____PPMImage__

#include <fstream>
#include <string.h>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <sstream>
#include <iostream>
#include <stdio.h>

#include "pixel.h"
using namespace std;

class PPMImage
{
private:
	char magicNumber[3];
	char comments[20];
	int numberColumns;
	int numberRows;
	int maxRGB;
	Pixel ***pixels;
	
	
public:
	PPMImage();
	PPMImage(int inNumberColumns,int inNumberRows,int inMaxRGB);
	PPMImage(int inNumberColumns,int inNumberRows,int inMaxRGB, Pixel ***inPixels);
	~PPMImage();
	void initFromFile(string inputFileName);
	string toString();
	string pixelsToString();
	
	char* getMagicNumber();
	char* getComments();
	int getNumberColumns();
	int getNumberRows();
	int getMaxRGB();
	Pixel***  getPixels();
	Pixel* getPixel(int column, int row);
	void setPixel(Pixel* pixel, int column, int row);
	
	
	
};

#endif /* defined(____PPMImage__) */
