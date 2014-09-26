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

string Pixel::toString()
{
    stringstream value;
    
    value << " " << red << " " << green << " " <<blue <<" ";
    
    return value.str();
}