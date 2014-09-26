
#include "rectangle.h"

Rectangle::Rectangle() 
{
    setXY(1, 1);
}

Rectangle::Rectangle(double x, double y) 
{
    setXY(x, y);
}

void Rectangle::setXY(double x, double y) 
{
    width = x;
    height = y;
}

double Rectangle::getArea(void) 
{
    return width*height;
}
