//rectangle.h

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
	private:
		double width;
		double height;

	public:
		Rectangle();
		Rectangle(double,double);
		void setXY(double,double);
		double getArea();

	
};

#endif
