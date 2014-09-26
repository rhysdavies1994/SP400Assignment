// classes example
#include <iostream>
#include "rectangle.h"
using namespace std;


//Program Takes command line parameters (instructions, one or more images, output filename)

int main()
{
    Rectangle rect;
    rect.setXY(3, 4);
    cout << "area: " << rect.getArea();



            //	arg[1] = instruction
            //	if(arg 1 is flip
            //		arg2 is value
            //	for( currentLength to lastLength)
            //	{
            //		run program
            //	}
            //	arg[last] = output

    return 0;
}


