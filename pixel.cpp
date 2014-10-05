/**************************************************************************
Class: 			Pixel
Owner:			Rhys Davies (16152939)
Description:	A Container Class for representing a RGBPixel, 
				this will be used inside of image classes to 
				build up the image.

**************************************************************************/

#include "pixel.h"

/**************************************************************************
Function: 		(constructor)Pixel
Imports:		none
Exports:		none
Description:	Initializes all class fields to default values

**************************************************************************/
Pixel::Pixel()
{
    red=0;
    green=0;
    blue=0;
}

/**************************************************************************
Function: 		(constructor)PPMImage
Imports:		int, int, int
Exports:		none
Description:	Takes input parameters for class fields to initialise 
				the object with certain values

**************************************************************************/
Pixel::Pixel(int inRed, int inGreen,int inBlue)
{
    red=inRed;
    green=inGreen;
    blue=inBlue;
}

/**************************************************************************
Function: 		Setters
Imports:		class values
Exports:		none
Description:	Takes input parameters for certain class fields to 
				initialise them to certain values

**************************************************************************/
void Pixel::setRGB(int inRed, int inGreen, int inBlue)
{
	red = inRed;
	green = inGreen;
	blue = inBlue;
}

void Pixel::setRed(int inRed)
{
	red=inRed;
}

void Pixel::setGreen(int inGreen)
{
	green=inGreen;
}

void Pixel::setBlue(int inBlue)
{
	blue=inBlue;
}

/**************************************************************************
Function:		Getters
Imports:		none
Exports:		class field type
Description:	Each getter returns the class field for acces outside of
				the class

**************************************************************************/
int Pixel::getRed()
{
	return red;
}

int Pixel::getGreen()
{
	return green;
}

int Pixel::getBlue()
{
	return blue;
}

string Pixel::toString()
{
    stringstream value;
    
    value << " " << red << " " << green << " " <<blue <<" ";
    
    return value.str();
}
