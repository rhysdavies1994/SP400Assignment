//
//  pixel.cpp
//  
//
//  Created by Rhys J Davies on 26/09/2014.
//
//

#include "pixel.h"


Pixel::Pixel()
{
    red=0;
    green=0;
    blue=0;
}

Pixel::Pixel(int inRed, int inGreen,int inBlue)
{
    red=inRed;
    green=inGreen;
    blue=inBlue;
}

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
