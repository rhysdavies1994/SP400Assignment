//
//  pixel.h
//  
//
//  Created by Rhys J Davies on 26/09/2014.
//
//

#ifndef ____pixel__
#define ____pixel__

#include <iostream>
#include <sstream>
using namespace std;


class Pixel
{
private:
    int red;
    int green;
    int blue;
public:
    Pixel();
    Pixel(int inRed,int inGreen,int inBlue);
    string toString();
	void setRed(int inRed);
	void setGreen(int inGreen);
	void setBlue(int inBlue);
	int getRed();
	int getGreen();
	int getBlue();
    
};

#endif /* defined(____pixel__) */
