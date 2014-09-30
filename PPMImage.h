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
	char* magicNumber;
	char* comments;
	int amountRows;
	int amountColumns;
	int maxRGB;
	Pixel ***pixels;
	
	
public:
	PPMImage();
	PPMImage(int inAmountRows,int inAmountColumns,int inMaxRGB, Pixel ***inPixels);
	~PPMImage();
	void initFromFile(string inputFileName);
	string toString();
	string pixelsToString();
	
	char* getMagicNumber();
	char* getComments();
	int getAmountRows();
	int getAmountColumns();
	int getMaxRGB();
	Pixel***  getPixels();
	Pixel* getPixel(int row, int column);
	
	
	
};

#endif /* defined(____PPMImage__) */
