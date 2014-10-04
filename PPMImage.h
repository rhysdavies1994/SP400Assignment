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
	char magicNumber[10];
	char comments[20];
	string sourceFileName;
	int numberColumns;
	int numberRows;
	int maxRGB;
	Pixel ***pixels;
	
	
public:
	PPMImage();
	PPMImage(int inNumberColumns,int inNumberRows,int inMaxRGB);
	~PPMImage();
	void initFromFile(string inputFileName);
	string toString();
	string pixelsToString();
	
	char* getMagicNumber();
	char* getComments();
	int getNumberColumns();
	int getNumberRows();
	int getMaxRGB();
	string getSourceFileName();
	Pixel***  getPixels();
	Pixel* getPixel(int column, int row);
	void setPixel(int inRed, int inGreen, int inBlue, int column, int row);
	
	
	
};

#endif /* defined(____PPMImage__) */
